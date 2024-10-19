function getFlights(date, destinationCity, callbackFunction) {
    console.log("in getFlights with destinationCity:", destinationCity);
    $.getJSON(
        "FlightsController",
        {action: "getFlights", date: date, destinationCity: destinationCity},
        callbackFunction
    );
}

function getHotels(date, city, callbackFunction) {
    console.log("in getHotels with city:", city);
    $.getJSON(
        "HotelsController",
        {action: "getHotels", date: date, city: city},
        callbackFunction
    );
}

function reserveFlight(flightId) {
    $.post(
        "FlightsController",
        {action: 'reserveFlight', flightId: flightId},
        function (response) {
            if (response.error && response.error !== "") {
                alert('Server error while reserving: ' + JSON.stringify(response));
            } else {
                updateFlightList();
            }
        },
        'json'
    );
}

function reserveHotel(hotelId) {
    $.post(
        "HotelsController",
        {action: 'reserveHotel', hotelId: hotelId},
        function (response) {
            if (response.error && response.error !== "") {
                alert('Server error while reserving: ' + JSON.stringify(response));
            } else {
                updateHotelList();
            }
        },
        'json'
    );
}

function updateFlightList() {
    let date = sessionStorage.getItem("date");
    let city = sessionStorage.getItem("city");

    getFlights(date, city, function (flights) {
        console.log('flights:', flights);

        let flightsTable = $("#flightsTable");
        flightsTable.html("");
        flightsTable.append("<tr style='background-color: mediumseagreen'><td>Id</td><td>Date</td>" +
            "<td>Destination City</td><td>Seats</td><td></td></tr>");

        flights.forEach(function (oneFlight) {
            let row = $("<tr></tr>");
            row.append("<td>" + oneFlight.flightId + "</td>" +
                "<td>" + oneFlight.flightDate + "</td>" +
                "<td>" + oneFlight.destinationCity + "</td>" +
                "<td>" + oneFlight.availableSeats + "</td>" +
                "<td><button onclick='reserveFlight(" + oneFlight.flightId + ")'>reserve</button>'</td>");
            flightsTable.append(row);
        });
    });
}

function updateHotelList() {
    let date = sessionStorage.getItem("date");
    let city = sessionStorage.getItem("city");

    getHotels(date, city, function (hotels) {
        console.log('hotels:', hotels);

        let hotelsTable = $("#hotelsTable");
        hotelsTable.html("");
        hotelsTable.append("<tr style='background-color: mediumseagreen'><td>Id</td><td>Name</td><td>Date</td>" +
            "<td>City</td><td>Free rooms</td><td></td></tr>");

        hotels.forEach(function (oneHotel) {
            let row = $("<tr></tr>");
            row.append("<td>" + oneHotel.hotelId + "</td>" +
                "<td>" + oneHotel.hotelName + "</td>" +
                "<td>" + oneHotel.hotelDate + "</td>" +
                "<td>" + oneHotel.availableRooms + "</td>" +
                "<td>" + oneHotel.city + "</td>" +
                "<td><button onclick='reserveHotel(" + oneHotel.hotelId + ")'>reserve</button>'</td>");
            hotelsTable.append(row);
        });
    });
}

function cancelAllReservations() {
    $.post(
        "ReservationsController",
        {action: "cancelAll"},
        function (response) {
            if (response.error && response.error !== "") {
                alert('Server error: ' + JSON.stringify(response));
            } else {
                console.log('done cancel all');
                updateFlightList();
                updateHotelList();
            }
        },
        'json'
    );
}


$(document).ready(function () {
    updateFlightList();

    $("#logoutButton").click(function () {
        $.post(
            "LogoutController",
            function (response) {
                if (response !== "") {
                    alert('Server error: ' + response);
                }
            },
            'json'
        );
        window.location.href = "./";
    });
});

