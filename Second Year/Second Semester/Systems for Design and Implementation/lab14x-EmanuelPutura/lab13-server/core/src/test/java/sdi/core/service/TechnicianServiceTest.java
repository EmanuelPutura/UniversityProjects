package sdi.core.service;

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
import static org.junit.Assert.assertTrue;

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(classes = {ITConfig.class})
@TestExecutionListeners({DependencyInjectionTestExecutionListener.class, DirtiesContextTestExecutionListener.class,
        TransactionalTestExecutionListener.class, DbUnitTestExecutionListener.class})
@DatabaseSetup("classpath:db-test/db-data.xml")
public class TechnicianServiceTest {
    @Autowired
    private TechnicianService technicianService;

    @Test
    public void getAll() {
        var elems = technicianService.getAll();
        assertEquals(elems.size(), 3);
    }

    @Test
    public void getAllFromPage() {
        var elems = technicianService.getAllFromPage(0, 1);
        assertEquals(elems.size(), 1);
    }

    @Test
    public void delete() {
        technicianService.delete(3L);
        assertEquals(2, technicianService.getAll().size());
    }

    @Test
    public void search() {
        var optional = technicianService.search(1L);
        assertTrue(optional.isPresent());
        assertEquals(optional.get().getLastName(), "TechL1");
    }
}
