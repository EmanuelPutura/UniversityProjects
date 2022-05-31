package sdi.core.model.entities;

import lombok.*;
import sdi.core.model.BaseEntity;

import javax.persistence.*;
import java.io.Serializable;

/*
    A team in the workshop, working on a certain task
    For the purpose of this homework, each team contains only one technician and some other people, who
    are not specified in this class definition
 */

@NamedEntityGraphs({
        @NamedEntityGraph(
                name = "WorkshopTeam.teamsWithTechnician",
                attributeNodes = @NamedAttributeNode("teamTechnician")
        ),
        @NamedEntityGraph(name = "WorkshopTeam.teamsWithTechnicianAndDevices",
                attributeNodes = @NamedAttributeNode(value = "teamTechnician",
                        subgraph = "Technician.techniciansWithDevices"),
                subgraphs = @NamedSubgraph(name = "Technician.techniciansWithDevices",
                        attributeNodes = @NamedAttributeNode(value = "repairedDevices")))
})
@Entity
@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
@ToString
public class WorkshopTeam extends BaseEntity<Long>  implements Serializable {
    private String teamName;

    @OneToOne
    @JoinColumn(name = "technicianId", unique = true)
    private Technician teamTechnician;
}
