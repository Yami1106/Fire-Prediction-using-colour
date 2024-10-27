document.addEventListener('DOMContentLoaded', function () {
    var typed = new Typed('#element', {
        strings: ['Call Fire Department-101', 'Call Ambulance-108', 'Call Police-100'],
        typeSpeed: 50,
        backSpeed: 25,
        backDelay: 1000,
        startDelay: 500,
        loop: true,
        showCursor: false
    });

    document.querySelectorAll('a[href^="#"]').forEach(anchor => {
        anchor.addEventListener('click', function (e) {
            e.preventDefault();
            const targetElement = document.querySelector(this.getAttribute('href'));
            window.scrollTo({
                top: targetElement.offsetTop - 80,
                behavior: 'smooth'
            });
        });
    });

    document.getElementById('home-link').addEventListener('click', function(e) {
        e.preventDefault();
        window.scrollTo({ top: 0, behavior: 'smooth' });
    });

    window.addEventListener('scroll', function () {
        let scrollPosition = window.pageYOffset;
        document.querySelector('.parallax-img').style.transform = 'translateY(' + scrollPosition * 0.5 + 'px)';
    });

    const tiles = document.querySelectorAll('.tile-section');
    window.addEventListener('scroll', () => {
        const scrollPosition = window.scrollY + window.innerHeight;
        tiles.forEach(tile => {
            if (scrollPosition > tile.offsetTop + 100) {
                tile.classList.add('tile-visible');
            } else {
                tile.classList.remove('tile-visible');
            }
        });
    });

    window.onscroll = function () {
        var navbar = document.getElementById("navbar");
        if (window.pageYOffset > 100) {
            navbar.classList.add("sticky");
        } else {
            navbar.classList.remove("sticky");
        }
    };

    const scrollableDiv = document.querySelector('.slide-track');
    if (scrollableDiv) {
        scrollableDiv.addEventListener('mouseover', () => {
            scrollableDiv.style.animationPlayState = 'paused';
        });

        scrollableDiv.addEventListener('mouseout', () => {
            scrollableDiv.style.animationPlayState = 'running';
        });
    }
});

function fetchDataFromSheet(){
    const sheetId = "1nLgtXfzGKW47lhCdYD04eA155NVrJASsNOrwnBw73hY";
    const sheetName = encodeURIComponent("Sheet1");
    const sheetURL = `https://docs.google.com/spreadsheets/d/${sheetId}/gviz/tq?tqx=out:csv&sheet=${sheetName}`;

    $.ajax({
    type: "GET",
    url: sheetURL,
    dataType: "text",
    success: function (response) {
        var data = $.csv.toObjects(response);

        if (data.length > 0) {
        var temperature = data[0].temperature;
        var humidity = data[0].humidity;

        document.getElementById("temperature").textContent = temperature;
        document.getElementById("humidity").textContent = humidity;
        updateRiskIndicator(temperature, humidity);
        updateTime();

        } else {
        console.log("No data available in CSV.");
        }
    },
    });

    }

function updateTime() {
    document.getElementById("lastUpdate").textContent = "Last updated: " + new Date().toLocaleString();
}

function updateRiskIndicator() {
    const temperature = parseFloat(document.getElementById("temperature").innerHTML);
    const humidity = parseFloat(document.getElementById("humidity").innerHTML);

    const highTempThreshold = 35;
    const highHumidityThreshold = 70;
    const lowHumidityThreshold = 30;

    let risk = 0;
    let riskText = "Normal";

    if (temperature > highTempThreshold) {
        risk += 50;
    }

    if (humidity > highHumidityThreshold) {
        risk += 25;
    } else if (humidity < lowHumidityThreshold) {
        risk += 50;
    }

    if (risk >= 75) {
        riskText = "High";
    } else if (risk >= 50) {
        riskText = "Moderate";
    } else if (risk >= 25) {
        riskText = "Low";
    }

    const marker = document.getElementById('riskMarker');
    marker.style.left = `${risk}%`;

    const riskTextElement = document.getElementById('riskText');
    riskTextElement.textContent = riskText;

    riskTextElement.style.color = risk >= 75 ? 'red' : risk >= 50 ? 'orange' : risk >= 25 ? 'yellow' : 'green';
    console.log(`Temperature: ${temperature}°C, Humidity: ${humidity}%, Risk: ${risk}%, Level: ${riskText}`);
}

function manualRefresh() {
    document.getElementById("update-indicator").style.display = "block";
    fetchDataFromSheet();
    setTimeout(() => {
        document.getElementById("update-indicator").style.display = "none";
    }, 1000);
    document.getElementById("lastUpdate").textContent = "Last updated: " + new Date().toLocaleString();
}

// Initial load
fetchDataFromSheet();

// Initial load
manualRefresh();

// Automatic refresh every 10 seconds
setInterval(manualRefresh, 2000);

// // Refresh data every 10 seconds
// setInterval(fetchDataFromSheet, 2000);
