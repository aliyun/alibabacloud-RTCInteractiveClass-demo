package com.alivc.base;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * ClassName: RandomString <br/>
 * Function: TODO 生成各种类型的随机数. <br/>
 * Reason:   TODO 用于给功能模块提供随机的各种字符串. <br/>
 * Date: 2018年11月10日  <br/>
 * @author tz
 * @version v0.0.1
 * @see
 * @since JDK 1.8
 */
public class RandomString {
	public static final String SOURCES = "abcdefghijklmnopqrstuvwxyz1234567890-";
	public static final String SOURCES_NUMBER = "1234567890";
	public static final String SOURCES_AKS = "ABCDEFGHIJKLMNOPQRSTYVWXYZabcdefghijklmnopqrstuvwxyz1234567890-";
	public static final String SOURCES_ST = "ABCDEFGHIJKLMNOPQRSTYVWXYZabcdefghijklmnopqrstuvwxyz1234567890-/=+";

    /**
     * 创建随机字符串
     *
     * @param random
     * @param characters
     * @param length
     * @return
     */
    public String generateString(Random random, String characters, int length) {
        char[] text = new char[length];
        for (int i = 0; i < length; i++) {
            text[i] = characters.charAt(random.nextInt(characters.length()));
        }

        return new String(text);
    }

    public static String getRandomStringAndNum(int l) {
        if (l < 0) {
            return "请输入大于等于0的正整数";
        }
        String val = "";
        for (int i = 0; i < l; i++) {
            Random random = new Random();
            String charOrNum = random.nextInt(2) % 2 == 0 ? "char" : "num";
            if ("char".equalsIgnoreCase(charOrNum)) {
                int bigOrSmall = random.nextInt(2) % 2 == 0 ? 65 : 97;
                val += (char)(bigOrSmall + random.nextInt(26));
            } else if ("num".equalsIgnoreCase(charOrNum)) {
                val += String.valueOf(random.nextInt(10));
            }
        }
        return val;
    }

    /**
     * 生成一个随机字符串（规则：时间戳+888888888888）
     *
     * @return
     */
    public String getNum() {
        return System.currentTimeMillis() + 888888888888L + "";
    }

    public static String getData() {
        List<Object> list = new ArrayList<Object>();
        Random r = new Random();
        String str = "";
        int digit = 6;
        for (int i = 0; i < digit; i++) {
            Integer x = r.nextInt(10);
            str += x.toString();
        }
        if (list.contains(str)) {
            getData();
        }
        return str;
    }

    /**
     * 生成随机英文名
     *
     * @return
     */
    public static String getRandomName() {
        Random random = new Random(System.currentTimeMillis());
        String[] surname = {"James", "John", "Robert", "Michael", "William", "David", "Richard", "Charles", "Joseph",
            "Thomas", "Christopher", "Daniel", "Paul", "Mark", "Donald", "George", "Kenneth", "Steven",
            "Edward", "Brian", "Ronald", "Anthony", "Kevin", "Jason", "Matthew", "Gary", "Timothy",
            "Jose", "Larry", "Jeffrey", "Frank", "Scott", "Eric", "Stephen", "Andrew", "Raymond",
            "Gregory", "Joshua", "Jerry", "Dennis", "Walter", "Patrick", "Peter", "Harold", "Douglas",
            "Henry", "Carl", "Arthur", "Ryan", "Roger", "Joe", "Juan", "Jack", "Albert", "Jonathan",
            "Justin", "Terry", "Gerald", "Keith", "Samuel", "Willie", "Ralph", "Lawrence", "Nicholas",
            "Roy", "Mary", "Patricia", "Linda", "Barbara", "Elizabeth", "Jennifer", "Maria", "Susan",
            "Margaret", "Dorothy", "Lisa", "Nancy", "Karen", "Betty", "Helen", "Sandra", "Donna",
            "Carol", "Ruth", "Sharon", "Michelle", "Laura", "Sarah", "Kimberly", "Deborah", "Jessica",
            "Shirley", "Cynthia", "Angela", "Melissa", "Brenda", "Amy", "Anna", "Rebecca", "Virginia",
            "Kathleen", "Pamela", "Martha", "Debra", "Amanda", "Stephanie", "Carolyn", "Christine",
            "Marie", "Janet", "Catherine", "Frances", "Ann", "Joyce", "Diane", "Alice", "Julie",
            "Heather", "Teresa", "Doris", "Gloria", "Evelyn", "Jean", "Cheryl", "Mildred", "Katherine",
            "Joan", "Ashley", "Judith", "Rose", "Janice", "Kelly", "Nicole", "Judy", "Christina",
            "Kathy", "Theresa", "Beverly", "Denise", "Tammy", "Irene", "Jane", "Lori", "Rachel",
            "Marilyn", "Andrea", "Kathryn", "Louise", "Sara", "Anne", "Jacqueline", "Wanda", "Bonnie",
            "Julia", "Ruby", "Lois", "Tina", "Phyllis", "Norma", "Paula", "Diana", "Annie", "Lillian",
            "Emily", "Robin", "Peggy", "Crystal", "Gladys", "Rita", "Dawn", "Connie", "Florence",
            "Tracy", "Edna", "Tiffany", "Carmen", "Rosa", "Cindy", "Grace", "Wendy", "Victoria", "Edith",
            "Kim", "Sherry", "Sylvia", "Josephine", "Thelma", "Shannon", "Sheila", "Ethel", "Ellen",
            "Elaine", "Marjorie", "Carrie", "Charlotte", "Monica", "Esther", "Pauline", "Emma",
            "Juanita", "Anita", "Rhonda", "Hazel", "Amber", "Eva", "Debbie", "April", "Leslie", "Clara",
            "Lucille", "Jamie", "Joanne", "Eleanor", "Valerie", "Danielle", "Megan", "Alicia", "Suzanne",
            "Michele", "Gail", "Bertha", "Darlene", "Veronica", "Jill", "Erin", "Geraldine", "Lauren",
            "Cathy", "Joann", "Lorraine", "Lynn", "Sally", "Regina", "Erica", "Beatrice", "Dolores",
            "Bernice", "Audrey", "Yvonne", "Annette", "June", "Samantha", "Marion", "Dana", "Stacy",
            "Ana", "Renee", "Ida", "Vivian", "Roberta", "Holly", "Brittany", "Melanie", "Loretta",
            "Yolanda", "Jeanette", "Laurie", "Katie", "Kristen", "Vanessa", "Alma", "Sue", "Elsie",
            "Beth", "Jeanne"};

        int index = random.nextInt(surname.length - 1);
        String name = surname[index];
        return name;
    }

}