$(function() {
  $('a[href*="#"]:not([href="#"])').click(function() {
    if (location.pathname.replace(/^\//,'') == this.pathname.replace(/^\//,'') && location.hostname == this.hostname) {
      var target = $(this.hash);
      target = target.length ? target : $('[name=' + this.hash.slice(1) +']');
      if (target.length) {
        $('html, body').animate({
          scrollTop: target.offset().top
        }, 500);
        return false;
      }
    }
  });
});




// This is my take on the ScrollFire feature
// While it is not *exactly* the same, the principal is the same:
// The background image when the page is loaded is GTR_top.jpg, and once the page is scrolled past the image, it changes, and the background colour changes aswell
// The image does not change back when you scroll back up, but instead loops when you scroll down once more, such that each time you preform a repetition of one scroll down and back up,
// the image and background colour changes to the next image/colour in the array imgURLs and carColours
// While this is not true ScrollFire, i enjoyed coding this and i feel that it is a very neat concept, and i hope it is acceptable to fit the ScrollFire requirements
var counter = -1;
var thresholdPassed = false;
$(function() {
    $(window).on("scroll", function() {
        var t = window.scrollY;
        var tintBG = document.getElementById("tintBG");
        var lrgImg = document.getElementsByClassName("large-img");
        var imgURLs = [
            "img/cars/Porsche_top.jpeg",
            "img/cars/NSX_top.jpeg",
            "img/cars/GTR_top.jpg"
        ];
        var carColours = [
            "rgba(3, 134, 186, 0.3)",
            "rgba(255, 255, 255, 0.2)",
            "rgba(0, 0, 0, 0.3)"
        ];
        console.log(t);
        if (t>=555 && thresholdPassed==false) {
            thresholdPassed=true;
            if (counter==2){
                counter=-1;
            }
            counter++;
            tintBG.style.backgroundColor = carColours[counter];
            lrgImg[0].style.backgroundImage = "url('"+imgURLs[counter]+"')";
        }
        if (t<555) {
                thresholdPassed=false;
            }
        
    });
});

function toggleProductId() {
    const reason = document.getElementById('reason').value;
    const productIdContainer = document.getElementById('product-id-container');

    if (reason === 'product-info') {
        productIdContainer.style.display = 'block';
    } else {
        productIdContainer.style.display = 'none';
    }
}

// Form validation function
function validateForm() {
    validateName();
    validatePhone();
    validateProductId();
    validateMessage();
}

// Name validation
function validateName() {
    const name = document.getElementById('name');
    const regex = /^[A-Za-z\s]+$/; // Only letters and spaces, no numbers
    if (name.value.length >= 3 && regex.test(name.value)) {
        name.classList.add('valid');
        name.classList.remove('invalid');
    } else {
        name.classList.add('invalid');
        name.classList.remove('valid');
    }
}

// Phone number validation (123 456 7890 format)
function validatePhone() {
    const phone = document.getElementById('phone');
    const regex = /^\d{3} \d{3} \d{4}$/; // Format: 123 456 7890
    if (regex.test(phone.value)) {
        phone.classList.add('valid');
        phone.classList.remove('invalid');
    } else {
        phone.classList.add('invalid');
        phone.classList.remove('valid');
    }
}

// Product ID validation (only when visible)
function validateProductId() {
    const productId = document.getElementById('product-id');
    const productCodes = ['#424E523334', '#5A5836520A', '#393131424B0A', '#47545833353832520A']; // Example product IDs
    if (productId.style.display !== 'none' && productCodes.includes(productId.value)) {
        productId.classList.add('valid');
        productId.classList.remove('invalid');
    } else {
        productId.classList.add('invalid');
        productId.classList.remove('valid');
    }
}

// Message validation (10-30 characters)
function validateMessage() {
    const message = document.getElementById('message');
    if (message.value.length >= 10) {
        message.classList.add('valid');
        message.classList.remove('invalid');
    } else {
        message.classList.add('invalid');
        message.classList.remove('valid');
    }
}