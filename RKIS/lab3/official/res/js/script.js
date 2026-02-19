document.addEventListener('DOMContentLoaded', function() {
    // Подсветка активного пункта меню
    const currentPage = window.location.pathname.split('/').pop();
    const navLinks = document.querySelectorAll('.nav__link');

    navLinks.forEach(link => {
        const href = link.getAttribute('href');
        if (href === currentPage ||
            (currentPage === '' && href === 'index.html') ||
            (currentPage === 'official/' && href === 'index.html')) {
            link.classList.add('active');
        }
    });

    // Плавная прокрутка к якорям
    document.querySelectorAll('a[href^="#"]').forEach(anchor => {
        anchor.addEventListener('click', function (e) {
            e.preventDefault();
            const target = document.querySelector(this.getAttribute('href'));
            if (target) {
                target.scrollIntoView({
                    behavior: 'smooth',
                    block: 'start'
                });
            }
        });
    });

    // Анимация при скролле
    const animateOnScroll = function() {
        const elements = document.querySelectorAll('.advantage, .cake-card, .review, .cake');

        elements.forEach(element => {
            const elementTop = element.getBoundingClientRect().top;
            const elementBottom = element.getBoundingClientRect().bottom;

            if (elementTop < window.innerHeight - 100 && elementBottom > 0) {
                element.style.opacity = '1';
                element.style.transform = 'translateY(0)';
            }
        });
    };

    // Начальные стили для анимации
    const elementsToAnimate = document.querySelectorAll('.advantage, .cake-card, .review, .cake');
    elementsToAnimate.forEach(element => {
        element.style.opacity = '0';
        element.style.transform = 'translateY(20px)';
        element.style.transition = 'opacity 0.6s, transform 0.6s';
    });

    // Анимация при загрузке и скролле
    window.addEventListener('load', animateOnScroll);
    window.addEventListener('scroll', animateOnScroll);

    // Обработка формы обратной связи
    const feedbackForm = document.querySelector('.submit-form');
    if (feedbackForm) {
        feedbackForm.addEventListener('submit', function(e) {
            e.preventDefault();
            alert('Спасибо за заявку! Мы свяжемся с вами в ближайшее время.');
            this.reset();
        });
    }

    // Обработка формы загрузки
    const uploadForm = document.querySelector('.upload-form');
    if (uploadForm) {
        uploadForm.addEventListener('submit', function(e) {
            e.preventDefault();
            alert('Файл успешно загружен!');
        });
    }

    // Добавление в корзину
    const cartButtons = document.querySelectorAll('.cake__buy_btn');
    cartButtons.forEach(button => {
        button.addEventListener('click', function() {
            const cakeCard = this.closest('.cake');
            const cakeTitle = cakeCard.querySelector('.cake__title').textContent;
            alert(`Торт "${cakeTitle}" добавлен в корзину!`);

            // Визуальный эффект
            this.textContent = '✓ Добавлено';
            this.style.background = '#4CAF50';
            setTimeout(() => {
                this.textContent = 'В корзину';
                this.style.background = '';
            }, 2000);
        });
    });

    // Параллакс эффект для баннера
    const banner = document.querySelector('.banner');
    if (banner) {
        window.addEventListener('scroll', () => {
            const scrolled = window.pageYOffset;
            banner.style.backgroundPositionY = scrolled * 0.5 + 'px';
        });
    }

    // Счетчик для статистики
    const stats = document.querySelectorAll('.stat__number');
    if (stats.length > 0) {
        const animateNumbers = () => {
            stats.forEach(stat => {
                // Полный текст
                const fullText = stat.textContent;

                // Только цифры
                const numberMatch = fullText.match(/\d+/);
                if (!numberMatch) return;

                const targetNumber = parseInt(numberMatch[0]);

                // Все символы
                const symbols = fullText.replace(/\d+/g, '');

                let currentNumber = 0;
                const step = Math.ceil(targetNumber / 50); // 50 шагов анимации

                const timer = setInterval(() => {
                    currentNumber += step;

                    if (currentNumber >= targetNumber) {
                        // Итоговое число с символами
                        stat.textContent = targetNumber + symbols;
                        clearInterval(timer);
                    } else {
                        // Показ итога
                        stat.textContent = currentNumber + symbols;
                    }
                }, 30);
            });
        };

        // Запуск анимации чисел, когда блок статистики появляется
        const aboutSection = document.querySelector('.about');
        if (aboutSection) {
            const observer = new IntersectionObserver((entries) => {
                entries.forEach(entry => {
                    if (entry.isIntersecting) {
                        // Сохранение оригинальных значений перед анимацией
                        const originalValues = [];
                        stats.forEach(stat => {
                            originalValues.push(stat.textContent);
                        });

                        animateNumbers();

                        // Отключение observer после анимации
                        observer.unobserve(entry.target);
                    }
                });
            }, { threshold: 0.5 }); // Срабатывает когда 50% блока видно

            observer.observe(aboutSection);
        }
    }
});