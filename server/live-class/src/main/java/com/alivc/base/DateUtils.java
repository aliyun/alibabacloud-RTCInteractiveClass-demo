package com.alivc.base;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.SimpleTimeZone;

/**
 * @author huangwenmin
 * @date 2019/3/8
 */
public class DateUtils {

    public static final String FORMAT = "yyyy-MM-dd HH:mm:ss";
    public static final String FORMAT_UTC = "yyyy-MM-dd'T'HH:mm:ss'Z'";

    public static Date toDate(String date, String format) {
        // yyyy-MM-dd HH:mm:ss
        if (null == date || null == format) {
            return null;
        }

        try {
            SimpleDateFormat dateFormat = new SimpleDateFormat(format);
            dateFormat.setLenient(false);
            return dateFormat.parse(date);
        } catch (Exception e) {
        }
        return null;
    }

    public static String toString(Date date, String format) {
        if (null == date || null == format) {
            return null;
        }

        try {
            SimpleDateFormat dateFormat = new SimpleDateFormat(format);
            return dateFormat.format(date);
        } catch (Exception e) {
        }
        return null;
    }

    public static Long getMin() {
        return ((System.currentTimeMillis() / 1000 / 60) % 3600) % 60;
    }

    public static Date getDateMin(int min, long diff) {
        return new Date(
            (System.currentTimeMillis() / (min * 60 * 1000) * (min * 60 * 1000) + (diff * min * 60 * 1000)));
    }

    public static long getMinMod(int min) {
        long delay = min * 60 * 1000 - System.currentTimeMillis() % (min * 60 * 1000);
        return delay;
    }

    public static Date getDateHour(int diff) {
        return new Date((System.currentTimeMillis() / (3600 * 1000) * (3600 * 1000) + (diff * 3600 * 1000)));
    }

    public static Date getDateHour(Date date, int diff) {
        return new Date((date.getTime() / (3600 * 1000) * (3600 * 1000) + (diff * 3600 * 1000)));
    }

    public static Date getDateDay(Date date, int diff) {
        return new Date(
            ((date.getTime() + 8 * 3600 * 1000) / (3600 * 1000 * 24) * (3600 * 1000 * 24) + ((diff) * 3600 * 1000 * 24)
                - 8 * 3600 * 1000));
    }

    public static Date getDateMonth(Date date, int diff) {
        Calendar cal = Calendar.getInstance();
        cal.setTime(date);
        cal.add(Calendar.MONDAY, diff);
        return toDate(toString(cal.getTime(), "yyyy-MM"), "yyyy-MM");
    }

    public static String getDateHour(int diff, String format) {
        Date date = new Date((System.currentTimeMillis() / (3600 * 1000) * (3600 * 1000) + (diff * 3600 * 1000)));
        if (null == date) {
            return null;
        }

        return toString(date, format);
    }

    public static String getDateHourUTC(int diff, String format) {
        Date date = new Date((System.currentTimeMillis() / (3600 * 1000) * (3600 * 1000) + (diff * 3600 * 1000)));
        if (null == date) {
            return null;
        }

        return toUTCString(date, format);
    }

    public static String toUTCString(Date date, String format) {
        if (null == date || null == format) {
            return null;
        }

        try {
            SimpleDateFormat dateFormat = new SimpleDateFormat(format);
            dateFormat.setTimeZone(new SimpleTimeZone(SimpleTimeZone.UTC_TIME, "UTC"));
            return dateFormat.format(date);
        } catch (Exception e) {
        }
        return null;
    }

    public static Date utcToDate(String strDate, String format) {
        if (null == strDate) {
            return null;
        }

        try {
            SimpleDateFormat dateFormat = new SimpleDateFormat(format);
            //            dateFormat.setTimeZone(new SimpleTimeZone(SimpleTimeZone.UTC_TIME, "UTC"));
            //            dateFormat.setLenient(false);
            Date date = dateFormat.parse(strDate);
            // To fix time change to 59:59 bug.
            return new Date(date.getTime() + 8 * 3600 * 1000);
        } catch (Exception e) {
        }
        return null;
    }

    public static boolean isDayLastHour(Date date) {
        return "23".equals(toString(date, "HH"));
    }

    public static boolean isDayFirstHour(Date date) {
        return "00".equals(toString(date, "HH"));
    }

    public static boolean isMonthLastDay(Date date) {
        Calendar c = Calendar.getInstance();
        c.setTime(date);
        c.set(Calendar.DAY_OF_MONTH, c.getActualMaximum(Calendar.DAY_OF_MONTH));

        return c.getTime().equals(date);
    }

    public static int getMonthDayCount(Date date) {
        Calendar c = Calendar.getInstance();
        c.setTime(date);
        return c.getActualMaximum(Calendar.DAY_OF_MONTH);
    }

    public static double getSecondDiff(Date date1, Date date2) {
        return (double)(date2.getTime() - date1.getTime()) / 1000.0;
    }

    public static int getDayDiff(Date date1, Date date2) {
        return (int)((date2.getTime() - date1.getTime()) / (3600 * 24 * 1000));
    }

    public static String generateLocalTime(Date time) {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        return dateFormat.format(time);
    }

    public static String generateUTCMicroTime(Date time) {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss:SSS'Z'");
        dateFormat.setTimeZone(new SimpleTimeZone(SimpleTimeZone.UTC_TIME, "UTC"));
        dateFormat.setLenient(false);
        return dateFormat.format(time);
    }

    public static String generateUTCTime(Date time) {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss'Z'");
        dateFormat.setTimeZone(new SimpleTimeZone(SimpleTimeZone.UTC_TIME, "UTC"));
        dateFormat.setLenient(false);
        return dateFormat.format(time);
    }

    public static Date utcToDate(String utc) {
        try {
            if (utc == null || "".equalsIgnoreCase(utc)) {
                return null;
            }
            SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss'Z'");
            df.setTimeZone(new SimpleTimeZone(0, "GMT"));
            return df.parse(utc);
        } catch (ParseException e) {
            e.printStackTrace();
            return null;
        }
    }
}
