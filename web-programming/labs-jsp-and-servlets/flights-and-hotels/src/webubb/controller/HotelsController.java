package webubb.controller;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import webubb.domain.Hotel;
import webubb.domain.DBManager;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;
import java.util.Objects;

public class HotelsController extends HttpServlet {
    public static String FLIGHT_RESERVATION_TYPE = "flight";
    public static String HOTEL_RESERVATION_TYPE = "hotel";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");
        if ("getHotels".equals(action)) {
            String date = request.getParameter("date");
            String city = request.getParameter("city");

            response.setContentType("application/json");

            DBManager dbmanager = DBManager.getInstance();
            List<Hotel> hotels = dbmanager.getHotels(date, city);

            JSONArray jsonAssets = new JSONArray();
            for (Hotel hotel : hotels) {
                JSONObject jObj = new JSONObject();
                jObj.put("hotelId", hotel.getHotelId());
                jObj.put("hotelName", hotel.getHotelName());
                jObj.put("hotelDate", hotel.getHotelDate());
                jObj.put("city", hotel.getCity());
                jObj.put("availableRooms", hotel.getAvailableRooms());
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

        int hotelId = Integer.parseInt(request.getParameter("hotelId"));

        DBManager dbManager = DBManager.getInstance();

        Hotel hotel = dbManager.getHotelById(hotelId);
        if (hotel == null) {
            response.getWriter().write("{\"error\":\"no hotel with that id\"}");
            response.setStatus(400);
            return;
        }
        if (!Objects.equals(hotel.getHotelDate(), sessionDate) || !Objects.equals(hotel.getCity(), sessionCity)) {
            response.getWriter().write("{\"error\":\"hotel does not match your date/destination\"}");
            response.setStatus(400);
            return;
        }
        if (hotel.getAvailableRooms() == 0) {
            response.getWriter().write("{\"error\":\"no more rooms...\"}");
            response.setStatus(400);
            return;
        }

        int reservationId = dbManager.addReservation(name, HOTEL_RESERVATION_TYPE, hotelId);
        ((List<Integer>) request.getSession().getAttribute("reservationIds")).add(reservationId);

        dbManager.setHotelAvailableRooms(hotelId, hotel.getAvailableRooms() - 1);

        response.getWriter().write("{\"status\":\"success\"}");
        response.setStatus(200);
    }
}
