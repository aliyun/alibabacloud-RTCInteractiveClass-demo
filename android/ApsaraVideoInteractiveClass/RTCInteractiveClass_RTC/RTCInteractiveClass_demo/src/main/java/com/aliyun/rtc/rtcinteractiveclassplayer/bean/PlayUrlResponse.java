package com.aliyun.rtc.rtcinteractiveclassplayer.bean;

public class PlayUrlResponse {

    private String result;
    private String requestId;
    private String message;
    private String code;
    private DataBean data;

    public String getResult() {
        return result;
    }

    public void setResult(String result) {
        this.result = result;
    }

    public String getRequestId() {
        return requestId;
    }

    public void setRequestId(String requestId) {
        this.requestId = requestId;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public String getCode() {
        return code;
    }

    public void setCode(String code) {
        this.code = code;
    }

    public DataBean getData() {
        return data;
    }

    public void setData(DataBean data) {
        this.data = data;
    }

    public static class DataBean {
        private PlayUrlBean playUrl;

        public PlayUrlBean getPlayUrl() {
            return playUrl;
        }

        public void setPlayUrl(PlayUrlBean playUrl) {
            this.playUrl = playUrl;
        }

        public static class PlayUrlBean {

            private String rts;
            private String flv;
            private String hls1;
            private String hls2;

            public String getRts() {
                return rts;
            }

            public void setRts(String rts) {
                this.rts = rts;
            }

            public String getFlv() {
                return flv;
            }

            public void setFlv(String flv) {
                this.flv = flv;
            }

            public String getHls1() {
                return hls1;
            }

            public void setHls1(String hls1) {
                this.hls1 = hls1;
            }

            public String getHls2() {
                return hls2;
            }

            public void setHls2(String hls2) {
                this.hls2 = hls2;
            }
        }
    }
}
