package webubb.domain;

public class Article {
    private int id;
    private String user;
    private String journal;
    private String summary;
    private String date;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getUser() {
        return user;
    }

    public void setUser(String user) {
        this.user = user;
    }

    public String getJournal() {
        return journal;
    }

    public void setJournal(String journal) {
        this.journal = journal;
    }

    public String getSummary() {
        return summary;
    }

    public void setSummary(String summary) {
        this.summary = summary;
    }

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public Article(int id, String user, String journal, String summary, String date) {
        this.id = id;
        this.user = user;
        this.journal = journal;
        this.summary = summary;
        this.date = date;
    }
}
