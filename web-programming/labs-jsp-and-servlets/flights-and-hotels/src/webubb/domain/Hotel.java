package webubb.domain;

public class Hotel {
    private int hotelId;
    private String hotelName;
    private String hotelDate;
    private String city;
    private int availableRooms;

    public Hotel(int hotelId, String hotelName, String hotelDate, String city, int availableRooms) {
        this.hotelId = hotelId;
        this.hotelName = hotelName;
        this.hotelDate = hotelDate;
        this.city = city;
        this.availableRooms = availableRooms;
    }

    public int getHotelId() {
        return hotelId;
    }

    public void setHotelId(int hotelId) {
        this.hotelId = hotelId;
    }

    public String getHotelName() {
        return hotelName;
    }

    public void setHotelName(String hotelName) {
        this.hotelName = hotelName;
    }

    public String getHotelDate() {
        return hotelDate;
    }

    public void setHotelDate(String hotelDate) {
        this.hotelDate = hotelDate;
    }

    public String getCity() {
        return city;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public int getAvailableRooms() {
        return availableRooms;
    }

    public void setAvailableRooms(int availableRooms) {
        this.availableRooms = availableRooms;
    }
}
