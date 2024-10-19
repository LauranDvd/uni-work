package webubb.domain;

public class Picture {
    private int pictureId;
    private int uploader;
    private String url;

    public Picture(int pictureId, int uploader, String url) {
        this.pictureId = pictureId;
        this.uploader = uploader;
        this.url = url;
    }

    public int getPictureId() {
        return pictureId;
    }

    public void setPictureId(int pictureId) {
        this.pictureId = pictureId;
    }

    public int getUploader() {
        return uploader;
    }

    public void setUploader(int uploader) {
        this.uploader = uploader;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }
}
