package webubb.domain;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DBManager {
    private static DBManager instance;
    private Statement statement;
    private Connection connection;

    private DBManager() {
        connect();
    }

    public static DBManager getInstance() {
        if (instance == null)
            instance = new DBManager();
        return instance;
    }

    private void connect() {
        try {
            Class.forName("org.gjt.mm.mysql.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/flights_hotels", "david", "password");
            statement = connection.createStatement();
        } catch (Exception ex) {
            System.out.println("connect error :" + ex.getMessage());
            ex.printStackTrace();
        }
    }

//    public User authenticate(String username, String password) {
//        ResultSet rs;
//        User u = null;
//        System.out.println(username + " " + password);
//        try {
//            rs = statement.executeQuery(
//                    "select * from users where username='" + username + "' and userPassword='" + password + "'"
//            );
//            if (rs.next()) {
//                u = new User(rs.getInt("userId"), rs.getString("username"), rs.getString("userPassword"));
//            }
//            rs.close();
//        } catch (SQLException e) {
//            e.printStackTrace();
//        }
//        return u;
//    }

    public List<Flight> getFlights(String date, String destinationCity) {
        System.out.println("db manager will get flights");
        List<Flight> flights = new ArrayList<>();
        ResultSet rs;
        try {
//            rs = statement.executeQuery(
//                    "select P.pictureId, P.uploader, P.url, sum(UPV.score) as totalScore" +
//                            " from pictures P left join userspicturesvotes UPV on P.pictureId=UPV.pictureId " +
//                            "group by P.pictureId, P.uploader, P.url " +
//                            " order by totalScore DESC " +
//                            "limit " + journalName
//            );
            rs = statement.executeQuery(
                    "select * " +
                            "from Flights " +
                            "where flightDate='" + date + "' and destinationCity='" + destinationCity + "' and availableSeats>0"
            );

            while (rs.next()) {
                System.out.println("dbmanager got a flight, id=" + rs.getInt("flightId"));
                flights.add(new Flight(
                        rs.getInt("flightId"),
                        rs.getString("flightDate"),
                        rs.getString("destinationCity"),
                        rs.getInt("availableSeats")
                ));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return flights;
    }

    public List<Hotel> getHotels(String date, String city) {
        System.out.println("db manager will get hotels");
        List<Hotel> hotels = new ArrayList<>();
        ResultSet rs;
        try {
            rs = statement.executeQuery(
                    "select * " +
                            "from Hotels " +
                            "where hotelDate='" + date + "' and city='" + city + "' and availableRooms>0"
            );

            while (rs.next()) {
                System.out.println("dbmanager got a hotel, id=" + rs.getInt("hotelId"));
                hotels.add(new Hotel(
                        rs.getInt("hotelId"),
                        rs.getString("hotelName"),
                        rs.getString("hotelDate"),
                        rs.getString("city"),
                        rs.getInt("availableRooms")
                ));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return hotels;
    }

    //    public List<Article> getOthersArticlesSince(String date, String userName) {
//        List<Article> articles = new ArrayList<>();
//        ResultSet rs;
//        try {
//            rs = statement.executeQuery(
//                    "select A.id, A.user, J.name AS journalName, A.summary, A.date " +
//                            "from articles A inner join journals J on A.journalId=J.id  " +
//                            "where date>='" + date + "' and A.user<>'" + userName + "'"
//            );
//
//            while (rs.next()) {
//                System.out.println("dbmanager got a article, id=" + rs.getInt("id"));
//                articles.add(new Article(
//                        rs.getInt("id"),
//                        rs.getString("user"),
//                        rs.getString("journalName"),
//                        rs.getString("summary"),
//                        rs.getString("date")
//                ));
//            }
//            rs.close();
//        } catch (SQLException e) {
//            e.printStackTrace();
//        }
//        return articles;
//    }
//
    public Flight getFlightById(int flightId) {
        ResultSet rs;
        Flight flight = null;
        try {
            rs = statement.executeQuery(
                    "select * " +
                            "from flights " +
                            "where flightId=" + flightId
            );

            if (rs.next()) {
                flight = new Flight(
                        rs.getInt("flightId"),
                        rs.getString("flightDate"),
                        rs.getString("destinationCity"),
                        rs.getInt("availableSeats")
                );
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return flight;
    }

    public Reservation getReservationById(int id) {
        ResultSet rs;
        Reservation reservation = null;
        try {
            rs = statement.executeQuery(
                    "select * " +
                            "from reservations " +
                            "where id=" + id
            );

            if (rs.next()) {
                reservation = new Reservation(
                        rs.getInt("id"),
                        rs.getString("person"),
                        rs.getString("type"),
                        rs.getInt("idReservedResource")
                );
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return reservation;
    }

    public Hotel getHotelById(int hotelId) {
        ResultSet rs;
        Hotel hotel = null;
        try {
            rs = statement.executeQuery(
                    "select * " +
                            "from hotels " +
                            "where hotelId=" + hotelId
            );

            if (rs.next()) {
                hotel = new Hotel(
                        rs.getInt("hotelId"),
                        rs.getString("hotelName"),
                        rs.getString("hotelDate"),
                        rs.getString("city"),
                        rs.getInt("availableRooms")
                );
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return hotel;
    }

    // returns the ID of the reservation which was just added
    public int addReservation(String person, String type, int idReservedResource) {
        try {
            String query = "insert into reservations(person, type, idReservedResource) values (?, ?, ?)";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setString(1, person);
            statement.setString(2, type);
            statement.setInt(3, idReservedResource);
            statement.executeUpdate();

            return getBiggestReservationId(); // the table uses AUTO_INCREMENT, so the biggest id is the latest
        } catch (SQLException e) {
            e.printStackTrace();
            return -1;
        }
    }

    private int getBiggestReservationId() {
        try {
            ResultSet rs = statement.executeQuery(
                    "select max(id) AS maxId from reservations"
            );

            int maxId = 0;
            if (rs.next()) {
                maxId = rs.getInt("maxId");
            }
            rs.close();
            return maxId;
        } catch (SQLException e) {
            e.printStackTrace();
            return -1;
        }
    }

    public void setFlightAvailableSeats(int flightId, int newAvailableSeats) {
        try {
            String query = "update flights set availableSeats=? where flightId=?";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setInt(1, newAvailableSeats);
            statement.setInt(2, flightId);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void setHotelAvailableRooms(int hotelId, int newAvailableRooms) {
        try {
            String query = "update hotels set availableRooms=? where hotelId=?";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setInt(1, newAvailableRooms);
            statement.setInt(2, hotelId);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void deleteReservation(int reservationId) {
        System.out.println("deleting reservation with id=" + reservationId);
        try {
            String query = "delete from reservations where id=?";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setInt(1, reservationId);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
