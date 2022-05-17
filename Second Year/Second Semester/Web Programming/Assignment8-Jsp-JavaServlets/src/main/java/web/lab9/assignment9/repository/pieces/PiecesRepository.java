package web.lab9.assignment9.repository.pieces;

import web.lab9.assignment9.exceptions.AppException;
import web.lab9.assignment9.model.PuzzlePiece;
import web.lab9.assignment9.repository.GenericRepository;

import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Optional;

public class PiecesRepository extends GenericRepository<String, PuzzlePiece> {
    public PiecesRepository(String configFilePath) throws AppException {
        super(configFilePath, "pieces", "html_id");
    }

    @Override
    public void save(PuzzlePiece entity) throws AppException {
        if (entity == null) {
            throw new AppException("Entity must not be null!");
        }

        String insertSqlQuery = "INSERT INTO pieces(html_id, css_background_img) VALUES(?, ?) ON CONFLICT(html_id) DO UPDATE " +
                "SET html_id = excluded.html_id, css_background_img = excluded.css_background_img";
        try(var connection = DriverManager.getConnection(databaseUrl, databaseUsername, databasePassword);
            var statement = connection.prepareStatement(insertSqlQuery);
        ) {
            statement.setString(1, entity.getHtmlId());
            statement.setString(2, entity.getCssBackgroundImgUrl());

            statement.executeUpdate();
        } catch (SQLException e) {
            throw new AppException(e.getMessage());
        }
    }

    @Override
    protected Optional<PuzzlePiece> getEntityFromResultSet(ResultSet resultSet) {
        try {
            if (resultSet.next()){
                String htmlId = resultSet.getString("html_id");
                String cssBackgroundImg = resultSet.getString("css_background_img");

                return Optional.of(new PuzzlePiece(htmlId, cssBackgroundImg));
            }
        } catch (SQLException e) {
            return Optional.empty();
        }
        return Optional.empty();
    }
}
