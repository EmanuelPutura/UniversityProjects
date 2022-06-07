package sdi.web.dto.movie;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.ToString;
import sdi.web.dto.BaseDto;

import java.util.Objects;

@NoArgsConstructor
@AllArgsConstructor
@Data
@ToString(callSuper = true)
public class MovieDto extends BaseDto {
    private String title;
    private Integer year;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || MovieDto.class != o.getClass()) return false;
        var dto = (MovieDto) o;
        return getId() != null && Objects.equals(getId(), dto.getId());
    }
}
