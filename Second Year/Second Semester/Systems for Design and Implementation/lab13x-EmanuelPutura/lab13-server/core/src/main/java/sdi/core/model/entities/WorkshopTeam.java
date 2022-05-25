package sdi.core.model.entities;

import lombok.*;
import org.hibernate.Hibernate;
import sdi.core.model.BaseEntity;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Objects;

/*
    A team in the workshop, working on a certain task
    For the purpose of this homework, each team contains only one technician and some other people, who
    are not specified in this class definition
 */
@Entity
@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
@ToString
public class WorkshopTeam extends BaseEntity<Long>  implements Serializable {
    private String teamName;

    @OneToOne(cascade = CascadeType.ALL)
    private Technician teamTechnician;
}
