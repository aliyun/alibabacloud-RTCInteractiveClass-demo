package com.alivc.liveclass.controller;


import com.alibaba.fastjson.JSONObject;

import com.alivc.base.ConfigMapUtil;
import com.alivc.base.ResponseResult;
import com.alivc.base.RtcOpenAPI;
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import java.util.UUID;

@Slf4j
@RestController
public class RtcauthController {

    @RequestMapping(value = "/getRtcAuth", method = RequestMethod.GET)
    public ResponseResult getRtcAuth(String platform, String channelId, String userId, String role) {
        log.debug(platform + "-" + channelId + "-" + userId + "-" + role);
        ResponseResult responseResult = new ResponseResult();
        userId = UUID.randomUUID().toString();
        try {
            JSONObject rtcToken = RtcOpenAPI.createToken(channelId, userId);
            responseResult.setData(rtcToken);
            String appId = ConfigMapUtil.getValueByKey("rtc.liveclass.appId");
            ScheduledDeleteChannel.addChannel(appId, channelId);
            return responseResult;
        } catch (Exception e) {
            responseResult.setResult("false");
            responseResult.setCode("500");
            log.error("create RTC token error", e);
        }
        return responseResult;
    }
}
