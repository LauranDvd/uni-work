package webubb.domain;

public class Flight {
    private int flightId;
    private String flightDate;
    private String destinationCity;
    private int availableSeats;

    public Flight(int flightId, String flightDate, String destinationCity, int availableSeats) {
        this.flightId = flightId;
        this.flightDate = flightDate;
        this.destinationCity = destinationCity;
        this.availableSeats = availableSeats;
    }

    public int getFlightId() {
        return flightId;
    }

    public void setFlightId(int flightId) {
        this.flightId = flightId;
    }

    public String getFlightDate() {
        return flightDate;
    }

    public void setFlightDate(String flightDate) {
        this.flightDate = flightDate;
    }

    public String getDestinationCity() {
        return destinationCity;
    }

    public void setDestinationCity(String destinationCity) {
        this.destinationCity = destinationCity;
    }

    public int getAvailableSeats() {
        return availableSeats;
    }

    public void setAvailableSeats(int availableSeats) {
        this.availableSeats = availableSeats;
    }
}
