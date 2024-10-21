document.addEventListener('DOMContentLoaded', function () {
    var typed = new Typed('#element', {
        strings: ['Call Fire Department-101', 'Call Ambulance-108', 'Call Police-100'],
        typeSpeed: 50,
        backSpeed: 25, // Optional: Adds a backspacing effect
        backDelay: 1000, // Optional: Adds a delay before starting backspacing
        startDelay: 500, // Optional: Adds a delay before starting the typing
        loop: true, // Optional: Loops the typing animation
        showCursor: false // Optional: Shows the blinking cursor
    });

    // Smooth scroll functionality with delay
    document.querySelectorAll('a[href^="#"]').forEach(anchor => {
        anchor.addEventListener('click', function (e) {
            e.preventDefault();
            const targetElement = document.querySelector(this.getAttribute('href'));

            // Smooth scroll to the element
            window.scrollTo({
                top: targetElement.offsetTop - 80, // Adjust for fixed header height
                behavior: 'smooth'
            });
        });
    });
document.getElementById('home-link').addEventListener('click', function(e) {
    e.preventDefault(); // Prevent default link behavior
    window.scrollTo({
        top: 0, // Scroll to the top of the page
        behavior: 'smooth' // Smooth scrolling effect
    });
});


    // Parallax effect
    window.addEventListener('scroll', function () {
        let scrollPosition = window.pageYOffset;
        document.querySelector('.parallax-img').style.transform = 'translateY(' + scrollPosition * 0.5 + 'px)';
    });

    // Tile transition effect
    const tiles = document.querySelectorAll('.tile-section');
    window.addEventListener('scroll', () => {
        const scrollPosition = window.scrollY + window.innerHeight;
        tiles.forEach(tile => {
            if (scrollPosition > tile.offsetTop + 100) { // +100 to ensure the effect starts a bit earlier
                tile.classList.add('tile-visible');
            } else {
                tile.classList.remove('tile-visible');
            }
        });
    });

    // Sticky navbar
    document.addEventListener('DOMContentLoaded', function () {
        window.onscroll = function () {
            var navbar = document.getElementById("navbar");
            if (window.pageYOffset > 100) {
                navbar.classList.add("sticky");
            } else {
                navbar.classList.remove("sticky");
            }
        };
    });

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

function updateTemperature() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("temperature").innerHTML = this.responseText;
            updateRiskIndicator(); // Call here
        }
    };
    xhttp.open("GET", "temperature", true);
    xhttp.send();
}

function updateHumidity() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("humidity").innerHTML = this.responseText;
            updateRiskIndicator(); // Call here
        }
    };
    xhttp.open("GET", "humidity", true);
    xhttp.send();
}

function updateTime() {
    document.getElementById("lastUpdate").textContent = "Last updated: " + new Date().toLocaleString();
}

function manualRefresh() {
    document.getElementById("update-indicator").style.display = "block";
    
    // Simulate updating temperature and humidity with random values
    document.getElementById("temperature").innerHTML = (Math.random() * (40 - 20) + 20).toFixed(1);
    document.getElementById("humidity").innerHTML = (Math.random() * (100 - 0) + 0).toFixed(1);
    
    updateRiskIndicator();
    
    setTimeout(function () {
        document.getElementById("update-indicator").style.display = "none";
    }, 1000);
    document.getElementById("lastUpdate").textContent = "Last updated: " + new Date().toLocaleString();
}

function updateRiskIndicator() {
    const temperature = parseFloat(document.getElementById("temperature").innerHTML);
    const humidity = parseFloat(document.getElementById("humidity").innerHTML);

    // Define thresholds
    const highTempThreshold = 35; // °C
    const highHumidityThreshold = 70; // %
    const lowHumidityThreshold = 30; // %

    let risk = 0;
    let riskText = "Normal";

    // Calculate risk based on temperature and humidity
    if (temperature > highTempThreshold) {
        risk += 50;
    }

    if (humidity > highHumidityThreshold) {
        risk += 25;
    } else if (humidity < lowHumidityThreshold) {
        risk += 50;
    }

    // Determine risk level
    if (risk >= 75) {
        riskText = "High";
    } else if (risk >= 50) {
        riskText = "Moderate";
    } else if (risk >= 25) {
        riskText = "Low";
    }

    // Update the risk marker position
    const marker = document.getElementById('riskMarker');
    marker.style.left = `${risk}%`;

    // Update the risk text
    const riskTextElement = document.getElementById('riskText');
    riskTextElement.textContent = riskText;

    // Change the color of the risk text based on the risk level
    if (risk >= 75) {
        riskTextElement.style.color = 'red';
    } else if (risk >= 50) {
        riskTextElement.style.color = 'orange';
    } else if (risk >= 25) {
        riskTextElement.style.color = 'yellow';
    } else {
        riskTextElement.style.color = 'green';
    }

    console.log(`Temperature: ${temperature}°C, Humidity: ${humidity}%, Risk: ${risk}%, Level: ${riskText}`);
}

// Initial load
document.addEventListener('DOMContentLoaded', function() {
    updateRiskIndicator();
});

// Automatic refresh every 10 seconds
setInterval(manualRefresh, 10000);






  
