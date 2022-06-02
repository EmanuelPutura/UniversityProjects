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
public class WorkshopTeamRepositoryTest {
    @Autowired
    private WorkshopTeamRepository workshopTeamRepository;

    @Test
    public void getWorkshopTeamByTeamName() {
        assertEquals("there should be 1 team", 1, workshopTeamRepository.getWorkshopTeamWithTeamName("Team1").size());
        assertEquals("there should be 0 teams", 0, workshopTeamRepository.getWorkshopTeamWithTeamName("none").size());
    }
}
