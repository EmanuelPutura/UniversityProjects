package sdi.web.config;

import org.springframework.context.annotation.*;
import org.springframework.context.support.PropertySourcesPlaceholderConfigurer;
import sdi.core.config.JPAConfig;

@Configuration
@ComponentScan({"sdi.core"})
@Import({JPAConfig.class})
@PropertySources({@PropertySource(value = "classpath:local/database.properties")})
public class AppLocalConfig {
    @Bean
    public static PropertySourcesPlaceholderConfigurer propertySourcesPlaceholderConfigurer() {
        return new PropertySourcesPlaceholderConfigurer();
    }
}
