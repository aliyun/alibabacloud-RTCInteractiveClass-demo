package com.alivc.liveclass.model;

/**
 * IM 系统群组
 * @author haihua.whh
 * @Date 2021/7/27 10:10 下午
 **/
public class Group {
    String room;//room no
    String imCid;//IM 系统返回的groupid
    String title;
    String ownerUid;

    public String getRoom() {
        return room;
    }

    public void setRoom(String room) {
        this.room = room;
    }

    public String getImCid() {
        return imCid;
    }

    public void setImCid(String imCid) {
        this.imCid = imCid;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getOwnerUid() {
        return ownerUid;
    }

    public void setOwnerUid(String ownerUid) {
        this.ownerUid = ownerUid;
    }

    @Override
    public String toString() {
        return "Group{" +
            "room='" + room + '\'' +
            ", imCid='" + imCid + '\'' +
            ", title='" + title + '\'' +
            ", ownerUid='" + ownerUid + '\'' +
            '}';
    }
}
