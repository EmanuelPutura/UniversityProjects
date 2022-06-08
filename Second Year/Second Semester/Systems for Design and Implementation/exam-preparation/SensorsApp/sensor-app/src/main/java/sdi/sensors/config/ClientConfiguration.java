package sdi.sensors.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

@Configuration
@ComponentScan({"sdi.sensors.service", "sdi.sensors.tcp", "sdi.sensors.view", "sdi.sensors.repository"})
public class ClientConfiguration {
    @Bean
    ExecutorService executorService() {
        return Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());
    }
}
