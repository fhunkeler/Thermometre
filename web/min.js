function sendData(a){console.log("Send Data",a),fetch("/api/config",{method:"POST",headers:{"Content-Type":"application/json"},body:JSON.stringify(a)})}function handleSubmits(a){a.preventDefault();const b=a.target,c=new FormData(b),d=Object.entries(Object.fromEntries(c)).reduce((a,[b,c])=>{if("tabs"!==b){const d=b.split(".");if(1===d.length)a[b]=c;else{let b=a;for(let a=0;a<d.length-1;a++)b[d[a]]||(b[d[a]]={}),b=b[d[a]];b[d[d.length-1]]=c}}return a},{});d.first_boot=!1,sendData(d)}const form=document.querySelector("#config");form.addEventListener("submit",handleSubmits);const getConfig=async()=>{try{console.log("get Config");const a=await fetch("/api/config",{headers:{"Content-type":"application/json","Cache-Control":"no-cache"}}),b=await a.json();console.log(b);const c=form.querySelectorAll("input, select");c.forEach(a=>{const c=a.name.split(".");let d=b;for(let b=0;b<c.length;b++)d=d[c[b]];a.value=d});const d=document.querySelector("#overlay");d.classList.add("hidden");const e=document.querySelector("#loading");e.classList.add("hidden")}catch(a){console.log("get config",JSON.stringify(a,null,2));const b=document.querySelector("#loading");b.classList.add("hidden");const c=document.querySelector("#error");c.classList.remove("hidden")}};window.addEventListener("load",getConfig);const showPassword=a=>{a.preventDefault();const b=a.target.previousElementSibling;b.type="password"===b.type?"text":"password";const c=a.target;c.classList.toggle("show")};document.querySelectorAll(".show-password").forEach(a=>{a.addEventListener("click",showPassword)});