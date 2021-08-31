package com.alivc.liveclass.service;

import java.util.Map;

import com.alivc.liveclass.model.Group;

/**
 * @author haihua.whh
 * @Date 2021/6/17 6:41 下午
 **/
public interface IRoomService {

    public void createRoom(Group group);

    public void joinRoom(String room,String appUid);

    public void leaveRoom(String room,String appUid);

    public void delRoom(String room);

    public String getRoomByAppUid(String appUid);

    /**
     *
     * @param room
     * @return
     */
    public Group getGroup(String room);
}
