package sdi.core.model.entities;

import lombok.*;
import org.jetbrains.annotations.NotNull;
import sdi.core.model.BaseEntity;
import org.hibernate.Hibernate;

import javax.persistence.*;
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

@NamedEntityGraphs({
        @NamedEntityGraph(
                name = "Device.devicesWithTechnicians",
                attributeNodes = @NamedAttributeNode("assignedTechnicians")
        ),

        @NamedEntityGraph(
                name = "Device.devicesWithClient",
                attributeNodes = @NamedAttributeNode("client")
        ),

        @NamedEntityGraph(
                name = "Device.devicesWithTechniciansAndClient",
                attributeNodes = {
                        @NamedAttributeNode("assignedTechnicians"),
                        @NamedAttributeNode("client")
                }
        )
})
@Entity
@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
@ToString(callSuper = true)
public class Device extends BaseEntity<Long> {
    private String type;
    private String brand;
    private String model;

    @ManyToOne
    @JoinColumn(name = "client_id", nullable = false)
    private Client client;

    @ManyToMany(mappedBy = "repairedDevices", fetch = FetchType.LAZY)
    @ToString.Exclude
    private Set<Technician> assignedTechnicians = new HashSet<>();

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || Hibernate.getClass(this) != Hibernate.getClass(o)) return false;
        Device device = (Device) o;
        return getId() != null && Objects.equals(getId(), device.getId());
    }

    @Override
    public int hashCode() {
        return getClass().hashCode();
    }
}
