document.addEventListener('DOMContentLoaded', function() {
    // Подсветка активного пункта в навигации
    const navLinks = document.querySelectorAll('.nav-link');
    const sections = document.querySelectorAll('.task-section');

    navLinks.forEach(link => {
        link.addEventListener('click', function(e) {
            e.preventDefault();
            const targetId = this.getAttribute('href');
            const targetElement = document.querySelector(targetId);

            if (targetElement) {
                targetElement.scrollIntoView({
                    behavior: 'smooth',
                    block: 'start'
                });
            }
        });
    });

    // Анимация при скролле
    const animateOnScroll = function() {
        const elements = document.querySelectorAll('.task-section, .demo-block, .card');

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
    const elementsToAnimate = document.querySelectorAll('.task-section, .card');
    elementsToAnimate.forEach(element => {
        element.style.opacity = '0';
        element.style.transform = 'translateY(20px)';
        element.style.transition = 'opacity 0.6s, transform 0.6s';
    });

    // Запуск анимации при загрузке и скролле
    window.addEventListener('load', animateOnScroll);
    window.addEventListener('scroll', animateOnScroll);

    // Подсветка активного раздела при скролле
    function highlightNav() {
        let scrollPosition = window.scrollY + 100;

        sections.forEach(section => {
            const sectionTop = section.offsetTop;
            const sectionBottom = sectionTop + section.offsetHeight;
            const sectionId = section.getAttribute('id');

            if (scrollPosition >= sectionTop && scrollPosition < sectionBottom) {
                navLinks.forEach(link => {
                    link.classList.remove('active');
                    if (link.getAttribute('href') === '#' + sectionId) {
                        link.classList.add('active');
                    }
                });
            }
        });
    }

    window.addEventListener('scroll', highlightNav);

    // Интерактивность для блоков
    const demoBlocks = document.querySelectorAll('.demo-block');
    demoBlocks.forEach(block => {
        block.addEventListener('click', function() {
            const text = this.textContent.trim();
            alert(`Вы нажали на блок: "${text}"`);

            // Визуальный эффект
            this.style.transform = 'scale(0.95)';
            setTimeout(() => {
                this.style.transform = '';
            }, 200);
        });
    });

    // Копирование Emmet кода
    const emmetBlocks = document.querySelectorAll('.emmet-code');
    emmetBlocks.forEach(block => {
        block.addEventListener('dblclick', function() {
            const text = this.textContent.replace(/<!--.*?-->/g, '').trim();
            navigator.clipboard.writeText(text).then(() => {
                // Временное уведомление
                const notification = document.createElement('div');
                notification.textContent = 'Emmet скопирован!';
                notification.style.position = 'fixed';
                notification.style.bottom = '20px';
                notification.style.right = '20px';
                notification.style.background = '#2c2c2c';
                notification.style.color = 'white';
                notification.style.padding = '10px 20px';
                notification.style.borderRadius = '5px';
                notification.style.zIndex = '9999';
                document.body.appendChild(notification);

                setTimeout(() => {
                    notification.remove();
                }, 2000);
            });
        });
    });
});