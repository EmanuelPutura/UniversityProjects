package sdi.web.controller;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class MovieController {
    @RequestMapping(value = "/")
    String startUpFunction() {
        return "Hello world!";
    }
}
