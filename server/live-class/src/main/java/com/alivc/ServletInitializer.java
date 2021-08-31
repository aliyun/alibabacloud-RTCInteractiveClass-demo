package com.alivc;
 
import org.springframework.boot.builder.SpringApplicationBuilder;
import org.springframework.boot.web.servlet.support.SpringBootServletInitializer;

/** 
 * ClassName: ServletInitializer <br/> 
 * Function: TODO 初始化. <br/> 
 * Reason:   TODO 初始化. <br/> 
 * Date:     2018年11月10日  <br/> 
 * @author   tz 
 * @version   v0.0.1
 * @since    JDK 1.8 
 * @see       
 */
public class ServletInitializer  extends SpringBootServletInitializer {
	
	
	   @Override
		protected SpringApplicationBuilder configure(SpringApplicationBuilder application) {
			return application.sources(Application.class);
		}
 
}
