package web.lab9.assignment9.repository.pieces;

import web.lab9.assignment9.exceptions.AppException;
import web.lab9.assignment9.model.PuzzlePiece;
import web.lab9.assignment9.repository.Repository;

public interface PiecesRepositoryFactory {
    static Repository<String, PuzzlePiece> getInstance(String realFilePath) {
        try {
            return new PiecesRepository(realFilePath);
        } catch (AppException e) {
            return null;
        }
    }
}
