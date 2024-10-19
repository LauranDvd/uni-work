package webubb.domain;

public class Reservation {
    private int id;
    private String person;
    private String type;
    private int idReservedResource;

    public Reservation(int id, String person, String type, int idReservedResource) {
        this.id = id;
        this.person = person;
        this.type = type;
        this.idReservedResource = idReservedResource;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getPerson() {
        return person;
    }

    public void setPerson(String person) {
        this.person = person;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public int getIdReservedResource() {
        return idReservedResource;
    }

    public void setIdReservedResource(int idReservedResource) {
        this.idReservedResource = idReservedResource;
    }
}
