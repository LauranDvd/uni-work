package webubb.controller;

import webubb.domain.Flight;
import webubb.domain.Hotel;
import webubb.domain.Reservation;
import webubb.domain.DBManager;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

public class ReservationsController extends HttpServlet {
    public static String FLIGHT_RESERVATION_TYPE = "flight";
    public static String HOTEL_RESERVATION_TYPE = "hotel";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (request.getSession().getAttribute("name") == null) {
            response.setStatus(401);
            return;
        }

        List<Integer> reservationIds = (List<Integer>) request.getSession().getAttribute("reservationIds");

//        response.getWriter().write("{\"error\":\"no reservations=" + reservationIds.size() +"\"}");

        DBManager dbManager = DBManager.getInstance();

        reservationIds.forEach(oneReservationId -> {
            Reservation reservation = dbManager.getReservationById(oneReservationId);
            if (reservation.getType().equals(FLIGHT_RESERVATION_TYPE)) {
                Flight flight = dbManager.getFlightById(reservation.getIdReservedResource());
                dbManager.setFlightAvailableSeats(flight.getFlightId(), flight.getAvailableSeats() + 1);
            } else {
                Hotel hotel = dbManager.getHotelById(reservation.getIdReservedResource());
                dbManager.setHotelAvailableRooms(hotel.getHotelId(), hotel.getAvailableRooms() + 1);
            }

            dbManager.deleteReservation(oneReservationId);
        });

        ((List<Integer>) request.getSession().getAttribute("reservationIds")).clear();

        response.getWriter().write("{\"status\":\"success\"}");
        response.setStatus(200);
    }
}
