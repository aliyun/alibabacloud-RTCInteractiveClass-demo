package com.alivc.liveclass.model;

/**
 * @author haihua.whh
 * @Date 2021/7/27 9:36 下午
 **/
public enum RoomRole {
    Teacher(0),
    Student(1);
    int role ;
    RoomRole(int role){
        this.role = role;
    }
    public int getRole(){
        return this.role;
    }
}
