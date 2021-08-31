package com.alivc.base;

import java.io.Serializable;

/**
 * ClassName: ConstanData <br/> Function: TODO 系统常量. <br/> Reason:   TODO 系统常量. <br/> Date:     2018年12月13日  <br/>
 *
 * @author tz
 * @version v0.0.1
 * @see
 * @since JDK 1.8
 */
public class ConstanData implements Serializable {

    private static final long serialVersionUID = -2219320746383133223L;
    public static final Integer PAGE_SIZE = 10;
    public static final Integer PAGE = 1;

    public static final String ERRORMSG_SERVERERROR = "服务端错误";
    public static final String ERRORMSG_TOKENLOSE = "token无效";
    public static final String ERRORMSG_NOTOKEN = "无token";
    public static final String ERRORMSG_CODETIMEOUT = "验证码超时";
    public static final String ERRORMSG_USERISLOCK = "用户已锁定";
    public static final String ERRORMSG_PARM = "参数错误";

    public static final String OK = "200";

    public static final String CREATED = "201";

    public static final String ACCEPTED = "202";

    public static final String NO_CONTENT = "204";

    public static final String PARAM_ERROR = "300";

    public static final String TOKEN_ERROR = "301";

    public static final String INVALID_REQUEST = "400";

    public static final String UNAUTHORIZED = "401";

    public static final String FORBIDDEN = "403";

    public static final String NOT_FOUND = "404";

    public static final String NOT_ACCEPTABLE = "406";

    public static final String GONE = "410";

    public static final String USERISLOCK = "411";

    public static final String UNPROCESABLE_ENTITY = "422";

    public static final String INTERNAL_SERVER_ERROR = "500";

    public static final String TIME_OUT = "600";

}
