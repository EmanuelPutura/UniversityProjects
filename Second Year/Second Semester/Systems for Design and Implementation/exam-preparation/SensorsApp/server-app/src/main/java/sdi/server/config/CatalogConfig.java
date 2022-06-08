package sdi.server.config;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

@Configuration
@ComponentScan({"sdi.server.repository", "sdi.server.service", "sdi.server.view"})
public class CatalogConfig {
}
