document.addEventListener('DOMContentLoaded', function () {
    var typed = new Typed('#element', {
        strings: ['Call Fire Department-101', 'Call Ambulance-108', 'Call Police-100'],
        typeSpeed: 50,
        backSpeed: 25, // Optional: Adds a backspacing effect
        backDelay: 1000, // Optional: Adds a delay before starting backspacing
        startDelay: 500, // Optional: Adds a delay before starting the typing
        loop: true, // Optional: Loops the typing animation
        showCursor: true // Optional: Shows the blinking cursor
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
});
