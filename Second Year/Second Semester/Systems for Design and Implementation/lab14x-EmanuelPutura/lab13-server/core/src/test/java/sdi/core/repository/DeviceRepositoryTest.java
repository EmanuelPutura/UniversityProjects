package sdi.core.repository;

import com.github.springtestdbunit.DbUnitTestExecutionListener;
import com.github.springtestdbunit.annotation.DatabaseSetup;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.TestExecutionListeners;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;
import org.springframework.test.context.support.DependencyInjectionTestExecutionListener;
import org.springframework.test.context.support.DirtiesContextTestExecutionListener;
import org.springframework.test.context.transaction.TransactionalTestExecutionListener;
import sdi.core.ITConfig;

import static org.junit.Assert.assertEquals;

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(classes = {ITConfig.class})
@TestExecutionListeners({
        DependencyInjectionTestExecutionListener.class,
        DirtiesContextTestExecutionListener.class,
        TransactionalTestExecutionListener.class,
        DbUnitTestExecutionListener.class
})
@DatabaseSetup("classpath:db-test/db-data.xml")
public class DeviceRepositoryTest {
    @Autowired
    private DeviceRepository deviceRepository;

    @Test
    public void getDevicesWithType() {
        assertEquals("there should be 1 device", 1, deviceRepository.getDeviceWithType("type1").size());
        assertEquals("there should be 0 devices", 0, deviceRepository.getDeviceWithType("none").size());
    }

    @Test
    public void getDevicesWithBrand() {
        assertEquals("there should be 1 device", 1, deviceRepository.getDeviceWithBrand("brand1").size());
        assertEquals("there should be 0 devices", 0, deviceRepository.getDeviceWithBrand("none").size());
    }
}
