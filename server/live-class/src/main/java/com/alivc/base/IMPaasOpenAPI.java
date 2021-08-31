package com.alivc.base;




import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.UUID;

import com.alivc.liveclass.model.IMLoginResult;
import com.aliyun.live_interaction20201214.Client;
import com.aliyun.live_interaction20201214.models.AddGroupMembersRequest;
import com.aliyun.live_interaction20201214.models.AddGroupMembersRequest.AddGroupMembersRequestRequestParams;
import com.aliyun.live_interaction20201214.models.AddGroupMembersRequest.AddGroupMembersRequestRequestParamsInitMembers;
import com.aliyun.live_interaction20201214.models.AddGroupMembersResponse;
import com.aliyun.live_interaction20201214.models.CreateGroupRequest;
import com.aliyun.live_interaction20201214.models.CreateGroupRequest.CreateGroupRequestRequestParams;
import com.aliyun.live_interaction20201214.models.CreateGroupRequest.CreateGroupRequestRequestParamsInitMembers;
import com.aliyun.live_interaction20201214.models.CreateGroupResponse;
import com.aliyun.live_interaction20201214.models.DismissGroupRequest;
import com.aliyun.live_interaction20201214.models.DismissGroupRequest.DismissGroupRequestRequestParams;
import com.aliyun.live_interaction20201214.models.DismissGroupResponse;
import com.aliyun.live_interaction20201214.models.GetLoginTokenRequest;
import com.aliyun.live_interaction20201214.models.GetLoginTokenRequest.GetLoginTokenRequestRequestParams;
import com.aliyun.live_interaction20201214.models.GetLoginTokenResponse;
import com.aliyun.live_interaction20201214.models.RemoveGroupMembersRequest;
import com.aliyun.live_interaction20201214.models.RemoveGroupMembersRequest.RemoveGroupMembersRequestRequestParams;
import com.aliyun.live_interaction20201214.models.RemoveGroupMembersResponse;
import com.aliyun.live_interaction20201214.models.SendMessageRequest;
import com.aliyun.live_interaction20201214.models.SendMessageRequest.SendMessageRequestRequestParams;
import com.aliyun.live_interaction20201214.models.SendMessageResponse;
import com.aliyun.teaopenapi.models.Config;
import lombok.extern.slf4j.Slf4j;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * @author haihua.whh
 * @Date 202/6/16 1:34 下午
 **/
@Slf4j
public class IMPaasOpenAPI {

    private static final Logger LOG = LoggerFactory.getLogger(IMPaasOpenAPI.class);


    private static Client client = null;

    public static synchronized Client getClient() throws Exception {
        if (client == null) {
            Config authConfig = new Config();
            authConfig.accessKeyId = ConfigMapUtil.getValueByKey("IM_AccessKeyId");
            authConfig.accessKeySecret = ConfigMapUtil.getValueByKey("IM_AccessKeySecret");
            authConfig.type = "access_key";
            authConfig.endpoint = "live-interaction.aliyuncs.com";
            return new Client(authConfig);
        }
        return client;
    }

    public static IMLoginResult getToken(String appKey, String devideId, String appUid) throws Exception {
        GetLoginTokenRequest request = new GetLoginTokenRequest();
        request.setAppId(ConfigMapUtil.getValueByKey("IM_AppId"));
        GetLoginTokenRequestRequestParams params = new GetLoginTokenRequestRequestParams();
        params.setAppKey(appKey);
        params.setAppUid(appUid);
        params.setDeviceId(devideId);
        request.setRequestParams(params);
        GetLoginTokenResponse response = IMPaasOpenAPI.getClient().getLoginToken(request);
        if (response.getBody().getCode().equals("0")) {
            IMLoginResult result = new IMLoginResult();
            result.setAccessToken(response.getBody().getResult().getAccessToken());
            result.setAccessTokenExpiredTime(response.getBody().getResult().getAccessTokenExpiredTime());
            result.setRefreshToken(response.getBody().getResult().getRefreshToken());
            return result;
        } else {
            throw new Exception("获取Token错误！");
        }
    }

    public static String createGroup(String title,String appUid) throws Exception {
        CreateGroupRequest request = new CreateGroupRequest();
        request.setAppId(ConfigMapUtil.getValueByKey("IM_AppId"));
        CreateGroupRequestRequestParams params = new CreateGroupRequestRequestParams();
        params.setCreatorAppUid(appUid);
        params.setTitle(title);
        params.setUuid(UUID.randomUUID().toString());
        params.setCreatorAppUid(appUid);
        List<CreateGroupRequestRequestParamsInitMembers> users = new ArrayList<CreateGroupRequestRequestParamsInitMembers>();
        CreateGroupRequestRequestParamsInitMembers member = new CreateGroupRequestRequestParamsInitMembers();
        member.setAppUid(appUid);
        member.setJoinTime(System.currentTimeMillis());
        member.setNick("主持人");
        member.setRole(1);//群主
        users.add(member);
        params.setInitMembers(users);
        request.setRequestParams(params);
        CreateGroupResponse response = IMPaasOpenAPI.getClient().createGroup(request);
        if (response.getBody().getCode().equals("0")){
            return response.getBody().getResult().getAppCid();
        } else {
            throw new Exception("创建群聊失败");
        }
    }

    public static boolean destoryGroup(String appCid,String appUid) throws Exception {
        DismissGroupRequest request = new DismissGroupRequest();
        request.setAppId(ConfigMapUtil.getValueByKey("IM_AppId"));
        DismissGroupRequestRequestParams params = new DismissGroupRequestRequestParams();
        params.setAppCid(appCid);
        params.setOperatorAppUid(appUid);

        request.setRequestParams(params);
        DismissGroupResponse response = IMPaasOpenAPI.getClient().dismissGroup(request);
        if (response.getBody().getCode().equals("0")){
            return true;
        } else {
            throw new Exception("解散群聊失败！");
        }
    }

    public static boolean joinChannel(String appCid, String appUid, String nickName, Integer role)
        throws Exception {
        AddGroupMembersRequest request = new AddGroupMembersRequest();
        request.setAppId(ConfigMapUtil.getValueByKey("IM_AppId"));
        AddGroupMembersRequestRequestParams params = new AddGroupMembersRequestRequestParams();
        params.setAppCid(appCid);
        List<AddGroupMembersRequestRequestParamsInitMembers> members = new ArrayList<>();
        AddGroupMembersRequestRequestParamsInitMembers member = new AddGroupMembersRequestRequestParamsInitMembers();
        member.setAppUid(appUid);
        member.setJoinTime(System.currentTimeMillis());
        member.setNick(nickName);
        member.setRole(role);
        members.add(member);
        params.setInitMembers(members);
        request.setRequestParams(params);
        AddGroupMembersResponse response = IMPaasOpenAPI.getClient().addGroupMembers(request);
        LOG.info("RequestId {},Code {}, Message {}", response.getBody().getRequestId(), response.getBody().getCode(),
            response.getBody().getMessage());
        if (response.getBody().getCode().equals("0")) {
            return true;
        } else {
            return false;
        }
    }

    public static boolean leaveChannel(String appCid, String appUid, String ownerUid)
        throws Exception {
        log.info("leaveChannel params:appCid:{},appUid:{},ownerUid:{}", appCid, appUid, ownerUid);
        RemoveGroupMembersRequest request = new RemoveGroupMembersRequest();
        request.setAppId(ConfigMapUtil.getValueByKey("IM_AppId"));
        RemoveGroupMembersRequestRequestParams params = new RemoveGroupMembersRequestRequestParams();
        params.setAppCid(appCid);
        params.setAppUidsRemoved(new ArrayList<String>(Arrays.asList(appUid)));
        params.setOperatorAppUid(ownerUid);
        request.setRequestParams(params);
        RemoveGroupMembersResponse response = IMPaasOpenAPI.getClient().removeGroupMembers(request);
        LOG.info("RequestId {},Code {}, Message {}", response.getBody().getRequestId(), response.getBody().getCode(),
            response.getBody().getMessage());
        if (response.getBody().getCode().equals("0")) {
            return true;
        } else {
            return false;
        }
    }

    public static boolean sendMessage(String appCid, String sendUid,
                                      Integer conversationType, String content)
        throws Exception {
        SendMessageRequest request = new SendMessageRequest();
        request.setAppId(ConfigMapUtil.getValueByKey("IM_AppId"));
        SendMessageRequestRequestParams params = new SendMessageRequestRequestParams();
        params.setAppCid(appCid);
        params.setContent(content);
        //先只支持 文本类型；
        params.setContentType(1);
        params.setSenderId(sendUid);
        params.setUuid(UUID.randomUUID().toString());
        params.setConversationType(conversationType);
        request.setRequestParams(params);
        SendMessageResponse response = IMPaasOpenAPI.getClient().sendMessage(request);
        LOG.info("RequestId {},Code {}, Message {}", response.getBody().getRequestId(), response.getBody().getCode(),
            response.getBody().getMessage());
        if (response.getBody().getCode().equals("0")) {
            LOG.info("send success:MsgID {},createTime {}", response.getBody().getResult().getMsgId(),
                response.getBody().getResult().getCreateTime());
            return true;
        } else {
            return false;
        }
    }
}
