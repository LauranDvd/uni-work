package webubb.controller;

import java.io.IOException;
import java.util.ArrayList;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;


public class LoginController extends HttpServlet {

    public LoginController() {
        super();
    }

    protected void doPost(HttpServletRequest request,
                          HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String date = request.getParameter("date");
        String city = request.getParameter("city");
        RequestDispatcher requestDispatcher;

        requestDispatcher = request.getRequestDispatcher("/main_page.jsp");
        HttpSession session = request.getSession();
        session.setAttribute("name", name);
        session.setAttribute("date", date);
        session.setAttribute("city", city);
        session.setAttribute("reservationIds", new ArrayList<Integer>());

        requestDispatcher.forward(request, response);
    }

}