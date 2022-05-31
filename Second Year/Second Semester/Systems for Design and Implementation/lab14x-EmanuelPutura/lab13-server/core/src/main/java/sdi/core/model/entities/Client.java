package sdi.core.model.entities;

import lombok.*;
import sdi.core.model.BaseEntity;
import org.hibernate.Hibernate;

import javax.persistence.*;
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

@NamedEntityGraphs({
        @NamedEntityGraph(
                name = "Client.clientsWithDevices",
                attributeNodes = @NamedAttributeNode("clientDevices")
        ),
        @NamedEntityGraph(name = "Client.clientsWithDevicesAndTechnicians",
                attributeNodes = @NamedAttributeNode(value = "clientDevices",
                        subgraph = "Device.devicesWithTechnicians"),
                subgraphs = @NamedSubgraph(name = "Device.devicesWithTechnicians",
                        attributeNodes = @NamedAttributeNode(value = "assignedTechnicians")))
})
@Entity
@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
@ToString(callSuper = true)
public class Client extends BaseEntity<Long> {
    private String firstName;
    private String lastName;
    private String emailAddress;

    @OneToMany(mappedBy = "client", fetch = FetchType.LAZY)
    @ToString.Exclude
    private Set<Device> clientDevices = new HashSet<>();

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || Hibernate.getClass(this) != Hibernate.getClass(o)) return false;
        Client client = (Client) o;
        return getId() != null && Objects.equals(getId(), client.getId());
    }

    @Override
    public int hashCode() {
        return getClass().hashCode();
    }
}
