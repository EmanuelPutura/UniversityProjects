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
public class TechnicianRepositoryTest {
    @Autowired
    private TechnicianRepository technicianRepository;

    @Test
    public void getTechniciansWithFirstName() {
        assertEquals("there should be 1 technician", 1, technicianRepository.getTechnicianByFirstName("TechF1").size());
        assertEquals("there should be 0 technicians", 0, technicianRepository.getTechnicianByFirstName("none").size());
    }

    @Test
    public void getTechniciansWithLastName() {
        assertEquals("there should be 1 technician", 1, technicianRepository.getTechnicianByLastName("TechL1").size());
        assertEquals("there should be 0 technicians", 0, technicianRepository.getTechnicianByLastName("none").size());
    }
}
