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
                name = "Technician.techniciansWithDevices",
                attributeNodes = @NamedAttributeNode("repairedDevices")
        )
})
@Entity
@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
@ToString(callSuper = true)
public class Technician extends BaseEntity<Long> {
    private String firstName;
    private String lastName;
    private Long salary;

    @ManyToMany(fetch = FetchType.LAZY)
    @JoinTable(name = "RepairOrder",
        joinColumns = @JoinColumn(name = "technician_id", referencedColumnName = "id"),
        inverseJoinColumns = @JoinColumn(name = "device_id", referencedColumnName = "id")
    )
    @ToString.Exclude
    private Set<Device> repairedDevices = new HashSet<>();

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || Hibernate.getClass(this) != Hibernate.getClass(o)) return false;
        Technician technician = (Technician) o;
        return getId() != null && Objects.equals(getId(), technician.getId());
    }

    @Override
    public int hashCode() {
        return getClass().hashCode();
    }
}