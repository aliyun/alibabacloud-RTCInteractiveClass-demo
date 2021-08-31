package com.alivc.liveclass.service;

import java.time.Duration;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import com.alivc.liveclass.model.Group;
import com.alivc.liveclass.model.RoomRole;
import lombok.extern.slf4j.Slf4j;
import org.apache.commons.beanutils.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.stereotype.Service;

/**
 * @author haihua.whh
 * @Date 2021/6/17 6:41 下午
 **/
@Slf4j
@Service
public class RoomServiceImpl implements IRoomService {

    private static String GROUP_USER_LIST = "group_users:%s";
    private static String GROUP_KEY = "group:%s";

    @Autowired
    RedisTemplate redisTemplate;

    @Override
    public void createRoom(Group group) {
        try{
            Map<String, String> map = BeanUtils.describe(group);
            String groupKey = String.format(GROUP_KEY,group.getRoom());
            redisTemplate.opsForHash().putAll(groupKey,map);

            //设置有效期为7天
            redisTemplate.expire(groupKey, Duration.ofDays(7));

            String groupUserListKey = String.format(GROUP_USER_LIST,group.getRoom());
            redisTemplate.opsForZSet().add(groupUserListKey, group.getOwnerUid(), RoomRole.Teacher.getRole());
        }catch (Exception e){
            log.error("BeanUtils.describe error",e);
        }


    }

    @Override
    public void joinRoom(String room, String appUid) {
        String groupUserListKey = String.format(GROUP_USER_LIST,room);
        redisTemplate.opsForZSet().add(groupUserListKey, appUid, RoomRole.Student.getRole());
        //设置有效期为7天，防止积压
        redisTemplate.opsForValue().set(appUid,room,Duration.ofDays(7));
    }

    @Override
    public void leaveRoom(String room, String appUid) {
        String groupUserListKey = String.format(GROUP_USER_LIST,room);
        Long count = redisTemplate.opsForZSet().remove(groupUserListKey,appUid);
        boolean bool = redisTemplate.delete(appUid);
        log.info("leaveRoom: count:{}, bool:{}",count,bool);
    }

    @Override
    public void delRoom(String room) {
        String groupUserListKey = String.format(GROUP_USER_LIST,room);
        List<String> keys = new ArrayList<>();
        keys.add(groupUserListKey);
        String groupKey = String.format(GROUP_KEY,room);
        keys.add(groupKey);
        Long count = redisTemplate.delete(keys);
        log.info("delRoom: keys:{},count:{}", keys, count);
    }

    @Override
    public Group getGroup(String room) {
        String groupKey = String.format(GROUP_KEY,room);
        Group group = new Group();
        Map map = redisTemplate.opsForHash().entries(groupKey);
        try {
            BeanUtils.populate(group,map);
            return group;
        } catch (Exception e) {
            log.error("BeanUtils.populate error",e);
            return null;
        }
    }

    @Override
    public String getRoomByAppUid(String appUid){
        Object obj = redisTemplate.opsForValue().get(appUid);
        if (obj != null){
            return (String)obj;
        }
        return null;
    }
}
