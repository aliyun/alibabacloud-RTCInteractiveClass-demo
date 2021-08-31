package com.alivc.liveclass.controller;

import com.alibaba.fastjson.JSONObject;
import com.alivc.base.ConfigMapUtil;
import com.alivc.base.DateUtils;
import com.alivc.base.RtcOpenAPI;
import com.aliyuncs.rtc.model.v20180111.DescribeChannelUsersResponse;
import lombok.extern.slf4j.Slf4j;
import org.apache.commons.collections.CollectionUtils;
import org.apache.commons.lang3.StringUtils;
import org.apache.commons.lang3.tuple.ImmutablePair;

import java.time.LocalDateTime;
import java.time.ZoneOffset;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.ScheduledThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

@Slf4j
public class ScheduledDeleteChannel {

    private static final ScheduledExecutorService ScheduledExecutorService = new ScheduledThreadPoolExecutor(3);
    public static final ConcurrentMap<ImmutablePair<String, String>, JSONObject> TASKS = new ConcurrentHashMap<>();


    private static final String DURATION_LIMIT = ConfigMapUtil.getValueByKey("durationlimit");

    public static void addChannel(String appId, String channelId) {

        try {
            DescribeChannelUsersResponse response = RtcOpenAPI.describeChannelUsers(appId, channelId);
            if (CollectionUtils.isEmpty(response.getUserList())) {
                ImmutablePair<String, String> appChannel = new ImmutablePair<>(appId, channelId);

                ScheduledFuture scheduledFuture = TASKS.getOrDefault(appChannel, new JSONObject()).getObject("scheduledFuture", ScheduledFuture.class);
                if (scheduledFuture != null) {
                    try {
                        scheduledFuture.cancel(true);
                    } catch (Exception e) {
                        log.error("cancel error", e);
                    }
                }

                if (StringUtils.isNotBlank(DURATION_LIMIT) && Long.parseLong(DURATION_LIMIT) > 0) {

                    scheduledFuture = ScheduledExecutorService.schedule(() -> {
                        try {
                            RtcOpenAPI.deleteChannel(appId, channelId);
                            TASKS.remove(appChannel);
                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                    }, Long.parseLong(DURATION_LIMIT), TimeUnit.MINUTES);

                }

                JSONObject channelInfo = new JSONObject();
                channelInfo.put("scheduledFuture", scheduledFuture);
                channelInfo.put("channelStartTimeUtc", DateTimeFormatter.ofPattern(DateUtils.FORMAT_UTC).format(LocalDateTime.now(ZoneOffset.UTC.normalized())));

                TASKS.put(appChannel, channelInfo);

            }
        } catch (Exception e) {
            log.error("", e);
        }


    }


}






