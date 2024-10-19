package webubb.controller;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import webubb.domain.Flight;
import webubb.domain.DBManager;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;
import java.util.Objects;

public class FlightsController extends HttpServlet {
    public static String FLIGHT_RESERVATION_TYPE = "flight";
    public static String HOTEL_RESERVATION_TYPE = "hotel";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");
        if ("getFlights".equals(action)) {
            String date = request.getParameter("date");
            String destinationCity = request.getParameter("destinationCity");

            response.setContentType("application/json");

            DBManager dbmanager = DBManager.getInstance();
            List<Flight> flights = dbmanager.getFlights(date, destinationCity);

            JSONArray jsonAssets = new JSONArray();
            for (Flight flight : flights) {
                JSONObject jObj = new JSONObject();
                jObj.put("flightId", flight.getFlightId());
                jObj.put("flightDate", flight.getFlightDate());
                jObj.put("destinationCity", flight.getDestinationCity());
                jObj.put("availableSeats", flight.getAvailableSeats());
                jsonAssets.add(jObj);
            }
            PrintWriter out = new PrintWriter(response.getOutputStream());
            out.println(jsonAssets.toJSONString());
            out.flush();
        }
//        else if ("getAllArticlesSince".equals(action)) {
//            String dateStr = request.getParameter("date");
//
//            response.setContentType("application/json");
//            DBManager dbManager = DBManager.getInstance();
//            List<Article> recentArticles = dbManager.getOthersArticlesSince(dateStr, userName);
//            JSONArray recentJsonAssets = new JSONArray();
//            for (Article article : recentArticles) {
//                JSONObject jObj = new JSONObject();
//                jObj.put("id", article.getId());
//                jObj.put("user", article.getUser());
//                jObj.put("date", article.getDate());
//                jObj.put("summary", article.getSummary());
//                jObj.put("journal", article.getJournal());
//                recentJsonAssets.add(jObj);
//            }
//            PrintWriter recentOut = new PrintWriter(response.getOutputStream());
//            recentOut.println(recentJsonAssets.toJSONString());
//            recentOut.flush();
//        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (request.getSession().getAttribute("name") == null) {
            response.setStatus(401);
            return;
        }

        String name = (String) request.getSession().getAttribute("name");
        String sessionDate = (String) request.getSession().getAttribute("date");
        String sessionCity = (String) request.getSession().getAttribute("city");

        int flightId = Integer.parseInt(request.getParameter("flightId"));

        DBManager dbManager = DBManager.getInstance();

        Flight flight = dbManager.getFlightById(flightId);
        if (flight == null) {
            response.getWriter().write("{\"error\":\"no flight with that id\"}");
            response.setStatus(400);
            return;
        }
        if (!Objects.equals(flight.getFlightDate(), sessionDate) || !Objects.equals(flight.getDestinationCity(), sessionCity)) {
            response.getWriter().write("{\"error\":\"flight does not match your date/destination\"}");
            response.setStatus(400);
            return;
        }
        if (flight.getAvailableSeats() == 0) {
            response.getWriter().write("{\"error\":\"no more seats...\"}");
            response.setStatus(400);
            return;
        }

        int reservationId = dbManager.addReservation(name, FLIGHT_RESERVATION_TYPE, flightId);
        ((List<Integer>) request.getSession().getAttribute("reservationIds")).add(reservationId);

        dbManager.setFlightAvailableSeats(flightId, flight.getAvailableSeats() - 1);

        response.getWriter().write("{\"status\":\"success\"}");
        response.setStatus(200);
    }
}
