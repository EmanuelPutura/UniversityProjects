package sdi.core.model;

import lombok.*;
import org.hibernate.Hibernate;

import javax.persistence.Column;
import javax.persistence.Entity;
import java.util.Objects;

@Entity
@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
@ToString(callSuper = true)
public class Author extends BaseEntity<Long> {
    @Column(unique = true)
    private String name;

    private Integer rating;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || Hibernate.getClass(this) != Hibernate.getClass(o)) return false;
        var obj = (Author) o;
        return getId() != null && Objects.equals(getId(), obj.getId());
    }

    @Override
    public int hashCode() {
        return getClass().hashCode();
    }
}
