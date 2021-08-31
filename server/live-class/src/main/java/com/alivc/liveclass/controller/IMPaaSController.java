package com.alivc.liveclass.controller;

import java.util.HashMap;
import java.util.Map;

import com.alibaba.fastjson.JSON;

import com.alivc.base.IMPaasOpenAPI;
import com.alivc.liveclass.model.Group;
import com.alivc.liveclass.model.IMLoginResult;
import com.alivc.liveclass.model.IMOnlineOfflineNotify;
import com.alivc.liveclass.model.IMUserStatus;
import com.alivc.liveclass.model.Result;
import com.alivc.liveclass.service.IRoomService;
import lombok.extern.slf4j.Slf4j;
import org.apache.commons.lang3.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

/**
 * @author haihua.whh
 * @Date 2021/6/16 3:39 下午
 **/
@Slf4j
@RestController
public class IMPaaSController {



    @Autowired
    IRoomService roomService;

    @RequestMapping(value = "/im/login", method = {RequestMethod.GET, RequestMethod.POST})
    public Result login(String appKey, String deviceId, String appUid) {
        log.info("login param, appKey:{},deviceId:{},appUid:{}",appKey,deviceId,appUid);
        Result result = new Result();
        try {
            IMLoginResult r = IMPaasOpenAPI.getToken(appKey, deviceId, appUid);
            result.setCode(200);
            result.setData(r);
            return result;
        } catch (Exception e) {
            log.error("login error",e);
            result.setCode(500);
            result.setData("内部错误！error：" + e.getMessage());
            return result;
        }
    }

    @RequestMapping(value = "/im/createGroup", method = {RequestMethod.GET, RequestMethod.POST})
    public Result createGroup(String title, String appUid, String room) {
        log.info("createGroup param,title:{},appUid:{},room:{}",title,appUid,room);
        Result result = new Result();
        try {
            Group group = new Group();
            String cid = IMPaasOpenAPI.createGroup(title, appUid);
            group.setImCid(cid);
            group.setOwnerUid(appUid);
            group.setRoom(room);
            group.setTitle(title);
            roomService.createRoom(group);
            result.setCode(200);
            result.setData(cid);
            return result;
        } catch (Exception e) {
            log.error("createGroup error",e);
            result.setCode(500);
            result.setData("内部错误！error：" + e.getMessage());
            return result;
        }
    }

    @RequestMapping(value = "/im/getGroup", method = {RequestMethod.GET, RequestMethod.POST})
    public Result getGroup(String room) {
        log.info("getGroup params: room:{}",room);
        Result result = new Result();
        try {

            Group group = roomService.getGroup(room);
            if (group != null) {
                String cid = group.getImCid();
                result.setCode(200);
                result.setData(cid);
                return result;
            } else {
                result.setCode(404);
                result.setData("不存在该room的cid");
                return result;
            }
        } catch (Exception e) {
            log.error("getGroup error",e);
            result.setCode(500);
            result.setData("内部错误！error：" + e.getMessage());
            return result;
        }
    }


    @RequestMapping(value = "/im/leaveChannel", method = {RequestMethod.GET, RequestMethod.POST})
    public Result leaveChannel(String room,String appUid) {
        log.info("leaveChannel param,room:{},appUid:{}", room, appUid);
        roomService.leaveRoom(room,appUid);
        return new Result();
    }

    /**
     * 删除Im房间
     * @param room
     * @param appUid
     * @return
     */
    @RequestMapping(value = "/im/destoryChannel", method = {RequestMethod.GET, RequestMethod.POST})
    public Result destoryChannel(String room,String appUid) {
        log.info("destoryChannel,params:room:{},appUid{}",room,appUid);
        Group group = roomService.getGroup(room);
        if (group != null) {
            log.info("destoryChannel group:{}",group);
            String ownerUid = group.getOwnerUid();
            if (ownerUid.equals(appUid)) {
                try{
                    IMPaasOpenAPI.destoryGroup(group.getImCid(),group.getOwnerUid());
                    roomService.delRoom(room);
                    log.info("destryRoom success");
                    return new Result(200);
                }catch (Exception e){
                    log.error("destryRoom error",e);
                }
            }
        }
        log.warn("destoryChannel fail, group:{}",group);
        return new Result(500);
    }

    /**
     * 加入Im房间
     * @param appCid
     * @param appUid
     * @param role
     * @param nickName
     * @param room
     * @return
     */
    @RequestMapping(value = "/im/joinChannel", method = {RequestMethod.GET, RequestMethod.POST})
    public Result joinChannel(String appCid, String appUid,Integer role,String nickName,String room) {
        log.info("joinChannel params:appCid:{},appUid:{},role:{},nickName:{},room:{}", appCid, appUid, role,
            nickName, room);
        Result result = new Result();
        try{
            boolean bool = IMPaasOpenAPI.joinChannel(appCid,appUid,nickName,role);
            if (bool){
                roomService.joinRoom(room,appUid);
                result.setData("加入成功！");
                result.setCode(200);
                return result;
            } else {
                result.setData("服务器内部问题，加入失败！");
                result.setCode(500);
                return result;
            }
        }catch (Exception e){
            log.error("joinChannel error",e);
            result.setData("服务器内部问题，加入失败！"+e.getMessage());
            result.setCode(500);
            return result;
        }
    }

    /**
     * 通过服务端发送消息，规避客户端直接发送消息需要服务端处理回调的问题；
     * 后续IM服务剥离这个强依赖以后可以选择直接从客户端发送消息；
     * @param appCid
     * @param sendUid
     * @param content
     * @return
     */
    @RequestMapping(value = "/im/sendMsg", method = {RequestMethod.GET, RequestMethod.POST})
    public Result sendMsg(String appCid,String sendUid,String content) {
        log.info("sendMsg params appCid:{},sendUid:{},content:{}",appCid,sendUid,content);
        Result result = new Result();
        try{
            if (StringUtils.isBlank(content)) {
                result.setCode(400);
                result.setData("content不能为空！");
                return result;
            }
            boolean bool = IMPaasOpenAPI.sendMessage(appCid,sendUid,2,this.buildMessage(content));
            if (bool){
                result.setData("发送成功！");
                result.setCode(200);
                return result;
            } else {
                result.setData("服务器内部问题，发送失败！");
                result.setCode(500);
                return result;
            }
        }catch (Exception e){
            log.error("sendMsg error",e);
            result.setData("服务器内部问题，发送失败！"+e.getMessage());
            result.setCode(500);
            return result;
        }
    }

    /**
     * 接收IM服务的回调信息，处理用户下线和掉线时，从Group中移除。
     * @param data
     * @param requestId
     * @param command
     * @param ispSignature
     * @param ispSignatureSecretKey
     * @return
     */
    @RequestMapping(value = "/im/callback", method = {RequestMethod.GET, RequestMethod.POST})
    public Result callback(String data, String requestId, String command, String ispSignature,
                           String ispSignatureSecretKey) {
        log.info("callback:requestId:{},command:{},data:{},ispSignature:{},ispSignatureSecretKey:{}",
            requestId, command, data, ispSignature, ispSignatureSecretKey);
        try {
            IMOnlineOfflineNotify notify = JSON.parseObject(data, IMOnlineOfflineNotify.class);
            /**
             * 用户登出或者掉线（包括杀APP）
             */
            if (command.equals("Event.ChangeStatus") && (notify.getStatus() == IMUserStatus.Offline.getStatus()
                || notify.getStatus() == IMUserStatus.Logout.getStatus())) {
                this.doLeaveChannel(notify);
            }
        } catch (Exception e) {
            log.error("JSON.parseObject error", e);
        }
        return new Result(200);
    }

    private void doLeaveChannel(IMOnlineOfflineNotify notify){
        log.info("doLeaveChannel {}",notify);
        String room = roomService.getRoomByAppUid(notify.getAppUid());
        Group group = roomService.getGroup(room);
        if (group != null) {
            try {
                if (!notify.getAppUid().equals(group.getOwnerUid())){
                    boolean bool = IMPaasOpenAPI.leaveChannel(group.getImCid(), notify.getAppUid(), group.getOwnerUid());
                } else {
                    log.warn("AppUID：{} is group owner ,group.ownerUid:{}",notify.getAppUid(),group.getOwnerUid());
                }
                roomService.leaveRoom(room,notify.getAppUid());
            } catch (Exception e) {
                log.error("callback leaveChannel error", e);
            }
        }
    }

    private String buildMessage(String content){
        if (content == null){
            return null;
        }
        Map<String,String> message = new  HashMap<>();
        message.put("text",content);
        return JSON.toJSONString(message);
    }
}
