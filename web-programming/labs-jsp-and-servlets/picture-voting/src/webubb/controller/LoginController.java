package webubb.controller;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import webubb.model.DBManager;
import webubb.domain.User;


public class LoginController extends HttpServlet {

    public LoginController() {
        super();
    }

    protected void doPost(HttpServletRequest request,
                          HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        RequestDispatcher requestDispatcher;

        DBManager dbmanager = new DBManager();
        User user = dbmanager.authenticate(username, password);
        if (user != null) {
            requestDispatcher = request.getRequestDispatcher("/main_page.jsp");
            HttpSession session = request.getSession();
            session.setAttribute("user", user);
        } else {
            requestDispatcher = request.getRequestDispatcher("/error.jsp");
        }
        requestDispatcher.forward(request, response);
    }

}