package web.web.config;

import org.springframework.context.annotation.*;
import org.springframework.context.support.PropertySourcesPlaceholderConfigurer;
import web.core.config.JpaConfig;

@Configuration
@ComponentScan({"web.core"})
@Import({JpaConfig.class})
@PropertySources({@PropertySource(value = "classpath:local/database.properties")})
public class AppLocalConfig {
    @Bean
    public static PropertySourcesPlaceholderConfigurer propertySourcesPlaceholderConfigurer() {
        return new PropertySourcesPlaceholderConfigurer();
    }
}
