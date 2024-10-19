package webubb.controller;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import webubb.domain.Article;
import webubb.model.DBManager;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.List;

public class ArticlesController extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (request.getSession().getAttribute("name") == null) {
            response.setStatus(401);
            return;
        }
        String userName = (String) request.getSession().getAttribute("name");

        String action = request.getParameter("action");
        if ("getArticles".equals(action)) {
            String journalName = request.getParameter("journalName");

            response.setContentType("application/json");

            DBManager dbmanager = DBManager.getInstance();
            List<Article> articles = dbmanager.getArticles(journalName, userName);

            JSONArray jsonAssets = new JSONArray();
            for (Article article : articles) {
                JSONObject jObj = new JSONObject();
                jObj.put("id", article.getId());
                jObj.put("user", article.getUser());
                jObj.put("date", article.getDate());
                jObj.put("summary", article.getSummary());
                jObj.put("journal", article.getJournal());
                jsonAssets.add(jObj);
            }
            PrintWriter out = new PrintWriter(response.getOutputStream());
            out.println(jsonAssets.toJSONString());
            out.flush();
        } else if ("getAllArticlesSince".equals(action)) {
            String dateStr = request.getParameter("date");

            response.setContentType("application/json");
            DBManager dbManager = DBManager.getInstance();
            List<Article> recentArticles = dbManager.getOthersArticlesSince(dateStr, userName);
            JSONArray recentJsonAssets = new JSONArray();
            for (Article article : recentArticles) {
                JSONObject jObj = new JSONObject();
                jObj.put("id", article.getId());
                jObj.put("user", article.getUser());
                jObj.put("date", article.getDate());
                jObj.put("summary", article.getSummary());
                jObj.put("journal", article.getJournal());
                recentJsonAssets.add(jObj);
            }
            PrintWriter recentOut = new PrintWriter(response.getOutputStream());
            recentOut.println(recentJsonAssets.toJSONString());
            recentOut.flush();
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (request.getSession().getAttribute("name") == null) {
            response.setStatus(401);
            return;
        }

        String userName = (String) request.getSession().getAttribute("name");

        String journalName = request.getParameter(("journalName"));
        String summary = request.getParameter(("summary"));

        DBManager dbManager = DBManager.getInstance();

        if (dbManager.getJournalByName(journalName) == null) {
            dbManager.addJournal(journalName);
        }
        int journalId = dbManager.getJournalByName(journalName).getId();

        dbManager.addArticle(userName, journalId, summary, getCurrentDateTime());

        response.getWriter().write("{\"status\":\"success\"}");
        response.setStatus(200);
    }

    private String getCurrentDateTime() {
        LocalDateTime now = LocalDateTime.now();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        return now.format(formatter);
    }
}
