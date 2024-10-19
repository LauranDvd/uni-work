package webubb.controller;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import webubb.domain.Picture;
import webubb.domain.User;
import webubb.model.DBManager;

import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Random;


@MultipartConfig(
        fileSizeThreshold = 1024 * 1024, // 1 MB
        maxFileSize = 1024 * 1024 * 10,      // 10 MB
        maxRequestSize = 1024 * 1024 * 100   // 100 MB
)
public class PicturesController extends HttpServlet {
    private static final String UPLOAD_DIRECTORY = "C:\\xampp2\\htdocs\\facultate\\web\\pics_app_images\\"; // TODO relative path

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");

        if (action != null && action.equals("getPics")) {
            int noPicsToLoad;
            try {
                noPicsToLoad = Integer.parseInt(request.getParameter("noPicsToLoad"));
            } catch (NumberFormatException e) {
                response.setStatus(400);
                return;
            }

            if (noPicsToLoad < 0) {
                response.setStatus(400);
                return;
            }

            if (request.getSession().getAttribute("user") == null) {
                response.setStatus(401);
                return;
            }

            response.setContentType("application/json");
            DBManager dbmanager = new DBManager();
            ArrayList<Picture> pictures = dbmanager.getPictures(noPicsToLoad);
            JSONArray jsonAssets = new JSONArray();
            for (int i = 0; i < pictures.size(); i++) {
                JSONObject jObj = new JSONObject();
                jObj.put("pictureId", pictures.get(i).getPictureId());
                jObj.put("uploaderId", pictures.get(i).getUploader());
                jObj.put("uploader", dbmanager.getUsernameById(pictures.get(i).getUploader()));
                jObj.put("url", pictures.get(i).getUrl());
                jObj.put("totalScore", dbmanager.getTotalScoreOfPicture(pictures.get(i).getPictureId()));
                jsonAssets.add(jObj);
            }
            PrintWriter out = new PrintWriter(response.getOutputStream());
            out.println(jsonAssets.toJSONString());
            out.flush();
        } else if (action != null && action.equals("getMyVote")) {
            int pictureId = Integer.parseInt(request.getParameter("pictureId"));
            int userId = ((User) request.getSession().getAttribute("user")).getUserId();

            response.setContentType("application/json");
            DBManager dbmanager = new DBManager();

            int myVote = dbmanager.getUsersVote(userId, pictureId);

            PrintWriter out = new PrintWriter(response.getOutputStream());
            out.println(myVote);
            out.flush();
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (request.getSession().getAttribute("user") == null) {
            response.setStatus(401);
            return;
        }

        String action = request.getParameter("action");
        if (action != null && action.equals("votePicture")) {
            System.out.println("received votepicture post call...");

            int score;
            try {
                score = Integer.parseInt(request.getParameter("score"));
            } catch (NumberFormatException e) {
                response.setStatus(400);
                return;
            }
            if (!(1 <= score && score <= 10)) {
                response.setStatus(400);
                return;
            }

            int userId = ((User) request.getSession().getAttribute("user")).getUserId();

            DBManager dbManager = new DBManager();
            dbManager.votePicture(userId, Integer.parseInt(request.getParameter("pictureId")), score);

            response.getWriter().write("Voted successfully");
            return;
        }

        String filename = getRandomFilename();
        Part filePart = request.getPart("uploadedPic");
        for (Part part : request.getParts()) {
            System.out.println("will write to: " + UPLOAD_DIRECTORY + filename);
            part.write(UPLOAD_DIRECTORY + filename);
        }
        response.getWriter().print("The file uploaded successfully.");

        DBManager dbManager = new DBManager();
        dbManager.savePicture(
                ((User) request.getSession().getAttribute("user")).getUserId(),
                filename
        );
    }

    private String getRandomFilename() {
        Random random = new Random();

        StringBuilder filename = new StringBuilder();
        for (int i = 0; i < 10; i++)
            filename.append(random.nextInt(10));

        return filename.toString();
    }
}
