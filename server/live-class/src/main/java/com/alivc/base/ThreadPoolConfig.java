package com.alivc.base;

import java.util.concurrent.ThreadPoolExecutor;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.scheduling.annotation.EnableAsync;
import org.springframework.scheduling.concurrent.ThreadPoolTaskExecutor;

/**
 * 数据收集配置，主要作用在于Spring启动时自动加载一个ExecutorService对象.
 * @author tz
 * @date 2019/4/19
 * 
 */
@Configuration
@EnableAsync
public class ThreadPoolConfig {
	
	/**
	 * 核心线程数（默认线程数）
	 */                                                      
	private static final int COREPOOLSIZE = 10;       		 
	/**                                                      
	 *  最大线程数                                           
	 */                                                      
	private static final int MAXPOOLSIZE = 100;			     
	/**                                                      
	 * 允许线程空闲时间（单位：默认为秒）                    
	 */                                                      
	private static final int KEEPALIVETIME = 10;			 
	/**                                                      
	 * 缓冲队列数                                            
	 */                                                      
	private static final int QUEUECAPACITY = 200;			 
	/**                                                      
	 * 线程池名前缀
	 */
	private static final String THREADNAMEPREFIX = "Aliyun-Service-";   
	
	@Bean
	public ThreadPoolTaskExecutor taskExecutor(){
		ThreadPoolTaskExecutor executor = new ThreadPoolTaskExecutor();
		executor.setCorePoolSize(COREPOOLSIZE);   
		executor.setMaxPoolSize(MAXPOOLSIZE);
		executor.setQueueCapacity(QUEUECAPACITY);
		executor.setKeepAliveSeconds(KEEPALIVETIME);
		executor.setThreadNamePrefix(THREADNAMEPREFIX);
		
		/**
		 * 线程池对拒绝任务的处理策略
		 */
		executor.setRejectedExecutionHandler(new ThreadPoolExecutor.CallerRunsPolicy());
		/**
		 * 初始化
		 */
		executor.initialize();
		return executor;
	} 
}