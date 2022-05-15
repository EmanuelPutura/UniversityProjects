package web.lab9.assignment9.model;

public class PuzzlePiece {
    private final String htmlId;
    private final String cssBackgroundImgUrl;

    public PuzzlePiece(String htmlId, String cssBackgroundImgUrl) {
        this.htmlId = htmlId;
        this.cssBackgroundImgUrl = cssBackgroundImgUrl;
    }

    public String getHtmlId() {
        return htmlId;
    }

    public String getCssBackgroundImgUrl() {
        return cssBackgroundImgUrl;
    }
}
