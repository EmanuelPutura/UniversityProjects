package web.lab9.assignment9.service;

import org.json.JSONObject;
import web.lab9.assignment9.exceptions.AppException;
import web.lab9.assignment9.model.PuzzlePiece;
import web.lab9.assignment9.repository.Repository;
import org.javatuples.Pair;

import java.util.List;
import java.util.Objects;

public class PiecesService extends GenericService<String, PuzzlePiece> {
    private Integer movesPerformed;
    private Boolean running;

    public PiecesService(Repository<String, PuzzlePiece> repository) {
        super(repository);
        setDefaultPieces();
        this.movesPerformed = 0;
        running = true;
    }

    private void setDefaultPieces() {
        try {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    var divHtmlId = getHtmlDivIdFromCoordinates(new Pair<>(i, j));
                    var cssBackgroundImgUrl = String.format("url(../resources/images/image%d%d.jpg)", i, j);

                    repository.save(new PuzzlePiece(divHtmlId, cssBackgroundImgUrl));
                }
            }

            // empty cell
            repository.save(new PuzzlePiece("piece10", ""));

            // wrong cells
            repository.save(new PuzzlePiece("piece20", "url(../resources/images/image10.jpg)"));
            repository.save(new PuzzlePiece("piece21", "url(../resources/images/image20.jpg)"));
            repository.save(new PuzzlePiece("piece22", "url(../resources/images/image21.jpg)"));
        }
        catch (Exception ignored) {}
    }

    private Pair<Integer, Integer> getCoordinatesFromHtmlId(String htmlDivId) {
        if (htmlDivId.length() < 2) {
            return null;
        }

        String lastTwoChars = htmlDivId.substring(htmlDivId.length() - 2);
        return new Pair<>(Integer.parseInt("" + lastTwoChars.charAt(0)), Integer.parseInt("" + lastTwoChars.charAt(1)));
    }

    private String getHtmlDivIdFromCoordinates(Pair<Integer, Integer> coordinates) {
        return "piece" + coordinates.getValue0().toString() + coordinates.getValue1().toString();
    }

    private boolean checkIfNeighbourCells(Pair<Integer, Integer> firstCell, Pair<Integer, Integer> secondCell) {
        int[][] variations = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int[] variation : variations) {
            if ((firstCell.getValue0() + variation[0]) == secondCell.getValue0() && (firstCell.getValue1() + variation[1]) == secondCell.getValue1()) {
                return true;
            }
        }

        return false;
    }

    private Boolean checkWinner() {
        List<PuzzlePiece> piecesList = null;

        try {
            piecesList = repository.findAll();
        } catch (AppException e) {
            return false;
        }

        for(var piece : piecesList) {
            var coordinates = getCoordinatesFromHtmlId(piece.getHtmlId());
            if (coordinates == null || coordinates.getValue0() == null || coordinates.getValue1() == null) {
                return false;
            }

            var expectedImgUrl = String.format("url(../resources/images/image%d%d.jpg)", coordinates.getValue0(), coordinates.getValue1());
            if ((!piece.getCssBackgroundImgUrl().equals("") && !(piece.getCssBackgroundImgUrl() == null)) && !piece.getCssBackgroundImgUrl().equals(expectedImgUrl)) {
                return false;
            }
        }

        return true;
    }

    public String onPuzzleCellClicked(String htmlDivId) {
        List<PuzzlePiece> piecesList = null;
        var jsonResponse = new JSONObject();

        if (!running) {
            jsonResponse.put("status", "Error");
            jsonResponse.put("error", "Game finished!");
            return jsonResponse.toString();
        }

        try {
            piecesList = repository.findAll();
        } catch (AppException e) {
            jsonResponse.put("status", "Error");
            jsonResponse.put("error", "Get all error");
            return jsonResponse.toString();
        }

        PuzzlePiece clickedPiece = null;
        for (var piece : piecesList) {
            if (Objects.equals(piece.getHtmlId(), htmlDivId)) {
                clickedPiece = piece;
                break;
            }
        }

        if (clickedPiece == null) {
            jsonResponse.put("status", "Error");
            jsonResponse.put("error", "Invalid div html id error");
            return jsonResponse.toString();
        }

        PuzzlePiece emptyPuzzlePiece = null;
        for (var piece : piecesList) {
            if (piece.getCssBackgroundImgUrl() == null || piece.getCssBackgroundImgUrl().equals("")) {
                emptyPuzzlePiece = piece;
                break;
            }
        }

        if (emptyPuzzlePiece == null) {
            jsonResponse.put("status", "Error");
            jsonResponse.put("error", "No empty cell error");
            return jsonResponse.toString();
        }

        var emptyCellCoordinates = getCoordinatesFromHtmlId(emptyPuzzlePiece.getHtmlId());
        if (emptyCellCoordinates == null) {
            jsonResponse.put("status", "Error");
            jsonResponse.put("error", "No empty cell error");
            return jsonResponse.toString();
        }

        var clickedCellCoordinates = getCoordinatesFromHtmlId(htmlDivId);
        if (!checkIfNeighbourCells(emptyCellCoordinates, clickedCellCoordinates)) {
            jsonResponse.put("status", "Invalid");
            jsonResponse.put("message", "Not neighbours");
            return jsonResponse.toString();
        }

        try {
            repository.save(new PuzzlePiece(emptyPuzzlePiece.getHtmlId(), clickedPiece.getCssBackgroundImgUrl()));
            repository.save(new PuzzlePiece(clickedPiece.getHtmlId(), emptyPuzzlePiece.getCssBackgroundImgUrl()));
        } catch (AppException e) {
            jsonResponse.put("status", "Error");
            jsonResponse.put("error", "Save error");
            return jsonResponse.toString();
        }

        var isWinner = checkWinner();

        jsonResponse.put("status", "OK");
        jsonResponse.put("firstDivId", emptyPuzzlePiece.getHtmlId());
        jsonResponse.put("firstDivImg", clickedPiece.getCssBackgroundImgUrl());
        jsonResponse.put("secondDivId", clickedPiece.getHtmlId());
        jsonResponse.put("secondDivImg", emptyPuzzlePiece.getCssBackgroundImgUrl());
        jsonResponse.put("win", isWinner.toString());

        movesPerformed += 1;

        if (isWinner) {
            jsonResponse.put("moves", movesPerformed.toString());
            running = false;
        }

        return jsonResponse.toString();
    }
}
