package com.alivc.base;

import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;

/**
 * ClassName:ConfigMapUtil <br/> Function: TODO 配置公共参数 <br/> Reason:   TODO 配置公共参数. <br/> Date:     2019年3月26日 下午3:13:07
 * <br/>
 *
 * @author 176xiangkou
 * @see
 * @since JDK 1.8
 */
public class ConfigMapUtil {
    private static Map<String, String> map = new HashMap<String, String>();

    static {
        try {
            InputStream resourceAsStream = Thread.currentThread().getContextClassLoader().getResourceAsStream(
                "application.properties");
            InputStreamReader inputStreamReader = new InputStreamReader(resourceAsStream, "utf-8");
            Properties properties = new Properties();
            properties.load(inputStreamReader);
            Enumeration enumeration = properties.propertyNames();
            while (enumeration.hasMoreElements()) {
                String key = (String)enumeration.nextElement();
                String value = properties.getProperty(key);
                map.put(key, value);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String getValueByKey(String key) {
        return map.get(key);
    }

    public static Map<String, String> getMap() {
        return map;
    }

    public static void setMap(Map<String, String> map) {
        ConfigMapUtil.map = map;
    }

}