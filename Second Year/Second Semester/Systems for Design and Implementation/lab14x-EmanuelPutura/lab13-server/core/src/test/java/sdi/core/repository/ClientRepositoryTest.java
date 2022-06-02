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
public class ClientRepositoryTest {
    @Autowired
    private ClientRepository clientRepository;

    @Test
    public void getClientsWithFirstName() {
        assertEquals("there should be 1 client", 1, clientRepository.getClientWithFirstName("Gigi1").size());
        assertEquals("there should be 0 clients", 0, clientRepository.getClientWithFirstName("Nobody").size());
    }

    @Test
    public void getClientsWithLastName() {
        assertEquals("there should be 1 client", 1, clientRepository.getClientWithLastName("Becali1").size());
        assertEquals("there should be 0 clients", 0, clientRepository.getClientWithLastName("Nobody").size());
    }
}
