title = "ludis86"
project = "API Doc"..[[

<!-- your html here -->

<script>
var projectname = "ludis86"
var projectsub = "libudis86 Lua bindings"

document.getElementById("product_logo").innerHTML = '<img src="../resources/lua-logo-'+projectname+'.png" alt="logo"/>'
document.getElementById("product_name").innerHTML = '<big>'+projectname+'</big>'
document.getElementById("product_description").innerHTML = projectsub
</script>
<style>
#content { width:initial ; }
</style>

]]

description = [[
	-- single module has no description
]]

readme = {
	"README.md",
	"CHANGELOG",
	"LICENSE",
}
file = {
	".",
}
dir = "luadoc"
ext = "html"
format = "discount"

