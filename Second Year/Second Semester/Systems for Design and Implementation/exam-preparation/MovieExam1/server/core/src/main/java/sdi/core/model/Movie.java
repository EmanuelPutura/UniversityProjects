package sdi.core.model;

import lombok.*;
import org.hibernate.Hibernate;

import javax.persistence.*;
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

@NamedEntityGraphs({
        @NamedEntityGraph(
                name = "Movie.movieWithActors",
                attributeNodes = @NamedAttributeNode("movieActors")
        )
})
@Entity
@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
@ToString(callSuper = true)
public class Movie extends BaseEntity<Long> {
    @Column(unique = true)
    private String title;

    private Integer year;

    @OneToMany(cascade = CascadeType.ALL, fetch = FetchType.LAZY)
    @JoinColumn(name="movie")
    @ToString.Exclude
    private Set<Actor> movieActors = new HashSet<>();

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || Hibernate.getClass(this) != Hibernate.getClass(o)) return false;
        var obj = (Movie) o;
        return getId() != null && Objects.equals(getId(), obj.getId());
    }

    @Override
    public int hashCode() {
        return getClass().hashCode();
    }
}
